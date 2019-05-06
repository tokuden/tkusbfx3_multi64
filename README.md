# tkusbfx3_multi64

# Description
このフォルダは、特電Artix-7ボード用のDLLとサンプルプロジェクトをまとめたものです。
64bit版のバイナリを出力し、複数のArtix-7bボードを同時に扱うことができます。
Visual Studio 2019のC++コンパイラでコンパイルします。

# ファイルとディレクトリ
- testapp  - USBを通じてBRAMやDDR3 SDRAMに読み書きするサンプルプロジェクトです。
           複数のAritx-7ボードをUSBの「シリアル番号」で区別して開くことができます。
- tkusbfx3.h                    DLLを使うためのヘッダファイルです。
- tkusbfx3.dll                  生成されたランタイムライブラリです。64bit形式です。
- tkusbfx3.lib                  Visual C++用のインポートライブラリです

# testappのビルド方法
+ (1) testapp\testapp.vcxproj をVisual Studui 2019で開きます。
+ (2) tkusbfx3.dllとtkusbfx3.libとtkusbfx3.hを最新のものにします。
+ (3) ビルドします。

---------------------

# Copyright 
(C)2014-2019 特殊電子回路株式会社
