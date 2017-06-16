
import os
import os.path
import sys

sources = ["Move.cpp","Piece.cpp","Board.cpp","Game.cpp"]

output = "shatranj"

include_path = "./"

print_only = False

def NeedToCompile(sourcefile,objectfile):
	# check if object file exists
	if(os.path.isfile(objectfile)):
		# check its time signature
		sourcetime = os.path.getmtime(sourcefile)
		objecttime = os.path.getmtime(objectfile)
		# leave a tolerance of 10 seconds to avoid any inaccurate time reporting
		if(sourcetime < (objecttime - 10)):
			return False
	return True

def Execute(command):
	if(print_only):
		print(command)
	else:
		print(command)
		os.system(command)

def GetObjectName(sourcename,windows_build):
	object_extension = ".o"
	if(windows_build):		object_extension = ".obj"
	objectname = sourcename[0:sourcename.rfind('.')] + object_extension
	return objectname

def CompileSource(sourcefile,windows_build):
	compiler = "g++"
	if(windows_build):		compiler = "mpicxx"
	if(NeedToCompile(sourcefile,GetObjectName(sourcefile,windows_build))):
		compile_string = compiler + " -I" + include_path + " -c " + sourcefile
		Execute(compile_string)
		return True
	return False

def CompileSources(windows_build):
	for source in sources:
		CompileSource(source,windows_build)

def Compile(windows_build):
	CompileSources(windows_build)

def Link(windows_build):
	compiler = "g++"
	if(windows_build):		compiler = "mpicxx"
	link_command = compiler + " "
	for source in sources:
		link_command = link_command + GetObjectName(source,windows_build) + " "
	link_command = link_command + "-o " + output
	Execute(link_command)

windows_build = False
if(len(sys.argv) > 1):
	if(sys.argv[1] == "-w"):
		windows_build = True

Compile(windows_build)
Link(windows_build)

