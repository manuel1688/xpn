/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "ioproxy-rpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
iopproc1_null_1(void *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_null,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_open_1(IOPOPEN1args *argp, IOPOPEN1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_OPEN,
		(xdrproc_t) xdr_IOPOPEN1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPOPEN1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_close_1(IOPCLOSE1args *argp, IOPCLOSE1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_CLOSE,
		(xdrproc_t) xdr_IOPCLOSE1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPCLOSE1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_creat_1(IOPCREAT1args *argp, IOPCREAT1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_CREAT,
		(xdrproc_t) xdr_IOPCREAT1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPCREAT1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_unlink_1(IOPUNLINK1args *argp, IOPUNLINK1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_UNLINK,
		(xdrproc_t) xdr_IOPUNLINK1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPUNLINK1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_read_1(IOPREAD1args *argp, IOPREAD1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_READ,
		(xdrproc_t) xdr_IOPREAD1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPREAD1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_write_1(IOPWRITE1args *argp, IOPWRITE1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_WRITE,
		(xdrproc_t) xdr_IOPWRITE1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPWRITE1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_mkdir_1(IOPMKDIR1args *argp, IOPMKDIR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_MKDIR,
		(xdrproc_t) xdr_IOPMKDIR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPMKDIR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_rmdir_1(IOPRMDIR1args *argp, IOPRMDIR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_RMDIR,
		(xdrproc_t) xdr_IOPRMDIR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPRMDIR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_opendir_1(IOPOPENDIR1args *argp, IOPOPENDIR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_OPENDIR,
		(xdrproc_t) xdr_IOPOPENDIR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPOPENDIR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_readdir_1(IOPREADDIR1args *argp, IOPREADDIR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_READDIR,
		(xdrproc_t) xdr_IOPREADDIR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPREADDIR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_closedir_1(IOPCLOSEDIR1args *argp, IOPCLOSEDIR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_CLOSEDIR,
		(xdrproc_t) xdr_IOPCLOSEDIR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPCLOSEDIR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_rename_1(IOPRENAME1args *argp, IOPRENAME1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_RENAME,
		(xdrproc_t) xdr_IOPRENAME1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPRENAME1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_getattr_1(IOPGETATTR1args *argp, IOPGETATTR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_GETATTR,
		(xdrproc_t) xdr_IOPGETATTR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPGETATTR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_setattr_1(IOPSETATTR1args *argp, IOPSETATTR1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_SETATTR,
		(xdrproc_t) xdr_IOPSETATTR1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPSETATTR1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_statfs_1(IOPSTATFS1args *argp, IOPSTATFS1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_STATFS,
		(xdrproc_t) xdr_IOPSTATFS1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPSTATFS1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_flush_1(IOPFLUSH1args *argp, IOPFLUSH1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_FLUSH,
		(xdrproc_t) xdr_IOPFLUSH1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPFLUSH1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_preload_1(IOPPRELOAD1args *argp, IOPPRELOAD1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_PRELOAD,
		(xdrproc_t) xdr_IOPPRELOAD1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPPRELOAD1res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
iopproc1_stafsserver_1(IOPSTAFSSERVER1args *argp, IOPSTAFSSERVER1res *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, IOPPROC1_STAFSSERVER,
		(xdrproc_t) xdr_IOPSTAFSSERVER1args, (caddr_t) argp,
		(xdrproc_t) xdr_IOPSTAFSSERVER1res, (caddr_t) clnt_res,
		TIMEOUT));
}