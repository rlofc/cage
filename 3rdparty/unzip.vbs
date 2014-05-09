Dim fileName, workingDir
fileName = WScript.Arguments(0)
workingDir = CreateObject("Scripting.FileSystemObject").GetAbsolutePathName(".")
Set objShell = CreateObject("Shell.Application")
Set objSource = objShell.NameSpace(workingDir & "\" & fileName).Items()
Set objTarget = objShell.NameSpace(workingDir & "\")
intOptions = 256
objTarget.CopyHere objSource, intOptions