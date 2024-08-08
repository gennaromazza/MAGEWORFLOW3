[Setup]
AppName=MageWorkflow
AppVersion=1.0
DefaultDirName={pf}\MageWorkflow
DefaultGroupName=MageWorkflow
OutputBaseFilename=MageWorkflowSetup
SetupIconFile=resources\logo.ico

[Files]
Source: "build\Release\MageWorkflow.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "resources\logo.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\MageWorkflow"; Filename: "{app}\MageWorkflow.exe"; IconFilename: "{app}\logo.ico"
