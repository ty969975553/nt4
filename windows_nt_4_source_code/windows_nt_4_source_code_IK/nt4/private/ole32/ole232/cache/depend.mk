# 
# Built automatically 
# 
 
# 
# Source files 
# 
 
$(OBJDIR)\cachenod.obj $(OBJDIR)\cachenod.lst: .\cachenod.cpp \
	$(CAIROLE)\common\cobjerr.h $(CAIROLE)\common\rpcferr.h \
	$(CAIROLE)\h\coguid.h $(CAIROLE)\h\compobj.h $(CAIROLE)\h\dvobj.h \
	$(CAIROLE)\h\initguid.h $(CAIROLE)\h\moniker.h $(CAIROLE)\h\ole2.h \
	$(CAIROLE)\h\ole2dbg.h $(CAIROLE)\h\oleguid.h $(CAIROLE)\h\scode.h \
	$(CAIROLE)\h\storage.h $(CAIROLE)\ih\debug.h $(CAIROLE)\ih\map_kv.h \
	$(CAIROLE)\ih\ole2sp.h $(CAIROLE)\ih\olecoll.h $(CAIROLE)\ih\olemem.h \
	$(CAIROLE)\ih\privguid.h $(CAIROLE)\ih\utils.h \
	$(CAIROLE)\ih\utstream.h $(CAIROLE)\ih\valid.h \
	$(CAIROLE)\ole232\inc\cachenod.h $(CAIROLE)\ole232\inc\gen.h \
	$(CAIROLE)\ole232\inc\mf.h $(CAIROLE)\ole232\inc\ole2int.h \
	$(CAIROLE)\ole232\inc\olecache.h $(CAIROLE)\ole232\inc\olepres.h \
	$(COMMON)\ih\dbgpoint.hxx $(COMMON)\ih\debnot.h $(COMMON)\ih\winnot.h \
	$(CRTINC)\ctype.h $(CRTINC)\excpt.h $(CRTINC)\malloc.h \
	$(CRTINC)\stdarg.h $(CRTINC)\stddef.h $(CRTINC)\stdlib.h \
	$(CRTINC)\string.h $(CRTINC)\wchar.h $(OSINC)\cderr.h \
	$(OSINC)\commdlg.h $(OSINC)\dde.h $(OSINC)\ddeml.h $(OSINC)\dlgs.h \
	$(OSINC)\drivinit.h $(OSINC)\lzexpand.h $(OSINC)\mmsystem.h \
	$(OSINC)\nb30.h $(OSINC)\ole.h $(OSINC)\rpc.h $(OSINC)\rpcdce.h \
	$(OSINC)\rpcdcep.h $(OSINC)\rpcnsi.h $(OSINC)\rpcnterr.h \
	$(OSINC)\shellapi.h $(OSINC)\widewrap.h $(OSINC)\winbase.h \
	$(OSINC)\wincon.h $(OSINC)\windef.h $(OSINC)\windows.h \
	$(OSINC)\winerror.h $(OSINC)\wingdi.h $(OSINC)\winmm.h \
	$(OSINC)\winnetwk.h $(OSINC)\winnls.h $(OSINC)\winnt.h \
	$(OSINC)\winperf.h $(OSINC)\winreg.h $(OSINC)\winsock.h \
	$(OSINC)\winspool.h $(OSINC)\winsvc.h $(OSINC)\winuser.h \
	$(OSINC)\winver.h

$(OBJDIR)\dacache.obj $(OBJDIR)\dacache.lst: .\dacache.cpp \
	$(CAIROLE)\ole232\inc\dacache.h $(CAIROLE)\ole232\inc\map_dwdw.h \
	$(CAIROLE)\ole232\inc\reterr.h $(CAIROLE)\common\cobjerr.h \
	$(CAIROLE)\common\rpcferr.h $(CAIROLE)\h\coguid.h \
	$(CAIROLE)\h\compobj.h $(CAIROLE)\h\dvobj.h $(CAIROLE)\h\initguid.h \
	$(CAIROLE)\h\moniker.h $(CAIROLE)\h\ole2.h $(CAIROLE)\h\ole2dbg.h \
	$(CAIROLE)\h\oleguid.h $(CAIROLE)\h\scode.h $(CAIROLE)\h\storage.h \
	$(CAIROLE)\ih\debug.h $(CAIROLE)\ih\map_kv.h $(CAIROLE)\ih\ole2sp.h \
	$(CAIROLE)\ih\olecoll.h $(CAIROLE)\ih\olemem.h \
	$(CAIROLE)\ih\privguid.h $(CAIROLE)\ih\utils.h \
	$(CAIROLE)\ih\utstream.h $(CAIROLE)\ih\valid.h \
	$(CAIROLE)\ole232\inc\ole2int.h $(COMMON)\ih\dbgpoint.hxx \
	$(COMMON)\ih\debnot.h $(COMMON)\ih\winnot.h $(CRTINC)\ctype.h \
	$(CRTINC)\excpt.h $(CRTINC)\malloc.h $(CRTINC)\stdarg.h \
	$(CRTINC)\stddef.h $(CRTINC)\stdlib.h $(CRTINC)\string.h \
	$(CRTINC)\wchar.h $(OSINC)\cderr.h $(OSINC)\commdlg.h $(OSINC)\dde.h \
	$(OSINC)\ddeml.h $(OSINC)\dlgs.h $(OSINC)\drivinit.h \
	$(OSINC)\lzexpand.h $(OSINC)\mmsystem.h $(OSINC)\nb30.h \
	$(OSINC)\ole.h $(OSINC)\rpc.h $(OSINC)\rpcdce.h $(OSINC)\rpcdcep.h \
	$(OSINC)\rpcnsi.h $(OSINC)\rpcnterr.h $(OSINC)\shellapi.h \
	$(OSINC)\widewrap.h $(OSINC)\winbase.h $(OSINC)\wincon.h \
	$(OSINC)\windef.h $(OSINC)\windows.h $(OSINC)\winerror.h \
	$(OSINC)\wingdi.h $(OSINC)\winmm.h $(OSINC)\winnetwk.h \
	$(OSINC)\winnls.h $(OSINC)\winnt.h $(OSINC)\winperf.h \
	$(OSINC)\winreg.h $(OSINC)\winsock.h $(OSINC)\winspool.h \
	$(OSINC)\winsvc.h $(OSINC)\winuser.h $(OSINC)\winver.h

$(OBJDIR)\olecache.obj $(OBJDIR)\olecache.lst: .\olecache.cpp \
	$(CAIROLE)\ih\ole1cls.h $(CAIROLE)\ole232\inc\cachenod.h \
	$(CAIROLE)\ole232\inc\olecache.h $(CAIROLE)\ole232\inc\olepres.h \
	$(CAIROLE)\common\cobjerr.h $(CAIROLE)\common\rpcferr.h \
	$(CAIROLE)\h\coguid.h $(CAIROLE)\h\compobj.h $(CAIROLE)\h\dvobj.h \
	$(CAIROLE)\h\initguid.h $(CAIROLE)\h\moniker.h $(CAIROLE)\h\ole2.h \
	$(CAIROLE)\h\ole2dbg.h $(CAIROLE)\h\oleguid.h $(CAIROLE)\h\scode.h \
	$(CAIROLE)\h\storage.h $(CAIROLE)\ih\debug.h $(CAIROLE)\ih\map_kv.h \
	$(CAIROLE)\ih\ole2sp.h $(CAIROLE)\ih\olecoll.h $(CAIROLE)\ih\olemem.h \
	$(CAIROLE)\ih\privguid.h $(CAIROLE)\ih\utils.h \
	$(CAIROLE)\ih\utstream.h $(CAIROLE)\ih\valid.h \
	$(CAIROLE)\ole232\inc\ole2int.h $(COMMON)\ih\dbgpoint.hxx \
	$(COMMON)\ih\debnot.h $(COMMON)\ih\winnot.h $(CRTINC)\limits.h \
	$(CRTINC)\ctype.h $(CRTINC)\excpt.h $(CRTINC)\malloc.h \
	$(CRTINC)\stdarg.h $(CRTINC)\stddef.h $(CRTINC)\stdlib.h \
	$(CRTINC)\string.h $(CRTINC)\wchar.h $(OSINC)\cderr.h \
	$(OSINC)\commdlg.h $(OSINC)\dde.h $(OSINC)\ddeml.h $(OSINC)\dlgs.h \
	$(OSINC)\drivinit.h $(OSINC)\lzexpand.h $(OSINC)\mmsystem.h \
	$(OSINC)\nb30.h $(OSINC)\ole.h $(OSINC)\rpc.h $(OSINC)\rpcdce.h \
	$(OSINC)\rpcdcep.h $(OSINC)\rpcnsi.h $(OSINC)\rpcnterr.h \
	$(OSINC)\shellapi.h $(OSINC)\widewrap.h $(OSINC)\winbase.h \
	$(OSINC)\wincon.h $(OSINC)\windef.h $(OSINC)\windows.h \
	$(OSINC)\winerror.h $(OSINC)\wingdi.h $(OSINC)\winmm.h \
	$(OSINC)\winnetwk.h $(OSINC)\winnls.h $(OSINC)\winnt.h \
	$(OSINC)\winperf.h $(OSINC)\winreg.h $(OSINC)\winsock.h \
	$(OSINC)\winspool.h $(OSINC)\winsvc.h $(OSINC)\winuser.h \
	$(OSINC)\winver.h

