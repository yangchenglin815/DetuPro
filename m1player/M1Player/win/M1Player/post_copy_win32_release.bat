@echo off

copy ..\Release\M1Player.lib	..\M1PlayerDemo\depends\lib\win\M1Player.lib
copy ..\Release\M1Player.lib	..\Test\m1player\M1Player.lib

copy ..\Release\M1Player.pdb	..\M1PlayerDemo\depends\lib\win\M1Player.pdb
copy ..\Release\M1Player.pdb	..\Test\m1player\M1Player.pdb

copy .\M1Player\M1Player.h	..\M1PlayerDemo\depends\header\m1player\M1Player.h
copy .\M1Player\M1Player.h	..\Test\m1player\M1Player.h

copy .\M1Player\MessageQueue.h	..\M1PlayerDemo\depends\header\m1player\MessageQueue.h
copy .\M1Player\MessageQueue.h	..\Test\m1player\MessageQueue.h

copy .\Error.h	..\M1PlayerDemo\depends\header\m1player\Error.h
copy .\Error.h	..\Test\m1player\Error.h