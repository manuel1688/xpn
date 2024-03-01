# XPN 2.3.0

*Expand Ad-Hoc Parallel File System*

[![License: GPL3](https://img.shields.io/badge/License-GPL3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
![version](https://img.shields.io/badge/version-2.3.0-blue)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/ca0c40db97f64698a2db9992cafdd4ab)](https://www.codacy.com/gh/xpn-arcos/xpn/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xpn-arcos/xpn&amp;utm_campaign=Badge_Grade)

* *Homepage*: <https://xpn-arcos.github.io/xpn-arcos.github.io/>
* *Source*:   <https://github.com/xpn-arcos/xpn>
* *Licence*:  [GNU GENERAL PUBLIC LICENSE Version 3](https://github.com/dcamarmas/xpn/blob/master/COPYING)</br>
* *Authors*:  Felix Garcia Carballeira, Luis Miguel Sanchez Garcia, Borja Bergua Guerra, Alejandro Calderon Mateos, Diego Camarmas Alonso, David Garcia Fernandez

## 1. To deploy XPN...

  The Expand Parallel File System (a.k.a. XPN) can be installed on a cluster with local storage per-node (HDD, SSD or RAM Drive) and a shared home directory.

  There are only two pre-requisites that XPN needs:
  1. The typical C development tools: gcc, make, and autotools
  2. An MPI implementation installed: MPICH 4.x

  The general steps to deploy XPN are:
  ```mermaid
  flowchart TD
    A[Start] --> B("Do you have 'Spack'?")

    B -- Yes --> X1
    subgraph ide1 [1 With spack]
    subgraph "1.1 Add repo"
       direction TB
       X1["git clone https://github.com/xpn-arcos/xpn.git<br> spack repo add xpn/scripts/spack"]
    end
    X1 --> X2
    subgraph "1.2 Install software"
       direction TB
       X2["`spack **info** xpn </br>
         spack **install** xpn`"]
    end
    X2 --> X3
    subgraph "1.3 Load software"
       direction LR
       X3["`spack **load** xpn`"]
    end
    classDef lt text-align:left,fill:lightgreen;
    class X1,X2,X3 lt;
    end
    X3 --> I[End]

    B -- No ---> Y1("Do you have 'modules'?")
    subgraph ide2 [2 With autotools]
    Y1-- Yes ---> Y1A
    subgraph "2.1 Install prerequisites"
       direction LR
       Y1A["module avail<br> module load gcc<br> module load 'impi/2017.4'"]
    end
    Y1-- No ---> Y1B
    subgraph "2.1 Install prerequisites"
       direction LR
       Y1B["sudo apt-get install -y autoconf automake gcc g++ make libtool build-essential<br> sudo apt-get install -y libmpich-dev mpich mpich-doc"]
    end
    Y1A --> Y2B
    Y1B --> Y2B
    subgraph "2.2 Download source code"
       direction LR
       Y2B["mkdir $HOME/src<br>
            cd    $HOME/src<br>
            git clone https://github.com/michaelrsweet/mxml.git<br>
            git clone https://github.com/xpn-arcos/xpn.git"]
    end
    Y2B --> Y3B
    subgraph "2.3 build source code"
       direction LR
       Y3B["cd $HOME/src <br>
            ./xpn/build-me -m 'full path to your mpicc compiler' \<br>
                           -i 'full path to where XPN and MXML are going to be installed'"]
    end

    classDef lt2 text-align:left,fill:lightblue;
    class Y1A,Y1B lt2;
    end

    Y3B --> I[End]
  ```


### With MPICH from source code

 In order to install the MPICH implementation of MPI from source code and with Infiniband (Omni-Path) support we recommend:
 ```
 wget https://www.mpich.org/static/downloads/4.1.1/mpich-4.1.1.tar.gz
 tar zxf mpich-4.1.1
 cd      mpich-4.1.1
 ./configure --prefix=<path where MPICH is going to be installed> \
             --enable-threads=multiple \
             --enable-romio \
             --with-device=ch4:ofi:psm2 \
             --with-libfabric=<path where your libfabric is installed>
 make
 make install
 ```


## 2. Executing XPN

First, you need to get familiar with 4 special files and 5 special environment variables for XPN client:

  ```mermaid
  mindmap
  root((XPN))
    files
        hostfile
        xpn cfg file
        nameserver
        server file
    environment variables
        XPN_DNS
        XPN_CONF
        XPN_THREAD
        XPN_SESSION
        XPN_LOCALITY
```

The 4 special files are:
* ```<hostfile>``` for MPI, it is a text file with the list of host names (one per line) where XPN servers and XPN client is going to be executed.
* ```<XPN configuration file>``` for XPN, it is a XML file with the configuration for the partition where files are stored at the XPN servers.
* ```<nameserver file>``` for XPN, it will be a text file (created at runtime) with the list of host names where XPN servers are executing.
* ```<server file>``` for XPN is a text file with the list of the servers to be stopped (one host name per line).

And the 5 special environment variables for XPN clients are:
* ```XPN_DNS```      with the full path to the nameserver file to be used (mandatory).
* ```XPN_CONF```     with the full path to the XPN configuration file to be used (mandatory).
* ```XPN_THREAD```   with value 0 for without threads, value 1 for thread-on-demand and value 2 for pool-of-threads (optional, default: 0).
* ```XPN_SESSION```  with value 0 for without session and value 1 for with session (optional, default: 0).
* ```XPN_LOCALITY``` with value 0 for without locality and value 1 for with locality (optional, default: 0).


### 2.1 Ad-Hoc Expand (based on MPI)
The typical executions has 3 main steps:
- First, launch the Expand MPI server (xpn_mpi_server):

  ```
  ./xpn -v -n <number of processes> -l <full path to the hostfile>  start
  ```

- Then,  launch the program that will use Expand (XPN client):

  ```
  mpiexec -np <number of processes> \
          -hostfile <full path to the hostfile> \
          -genv XPN_DNS  <nameserver file> \
          -genv XPN_CONF <XPN configuration file> \
          -genv LD_LIBRARY_PATH <INSTALL_PATH>/mxml/lib:$LD_LIBRARY_PATH \
          -genv LD_PRELOAD      <INSTALL_PATH>/xpn/lib/xpn_bypass.so:$LD_PRELOAD \
          <program path>
  ```

- At the end of your working session, you need to stop the MPI server (xpn_mpi_server):

  ```
  ./xpn -v -l <full path to the hostfile>  stop
  ```
    
Summary:

```mermaid
sequenceDiagram
    session        ->> xpn_mpi_server: launch the Expand MPI server
    xpn_mpi_server ->> mk_conf.sh: generate the XPN configuration file
    mk_conf.sh     ->> xpn.conf: generate the xpn.conf file
    xpn.conf      -->> xpn_mpi_server: read the XPN configuration file
    session        ->> XPN client: launch the program that will use Expand
    xpn.conf      -->> XPN client: read the XPN configuration file
    XPN client    -->> xpn_mpi_server: write and read data
    XPN client    -->> session: execution ends
    session        ->> xpn_mpi_server: stop the MPI server
```

