# tkusbfx3_multi64

# 説明
このレポジトリは、特電Artix-7ボード用のDLLとサンプルプロジェクトをまとめたものです。
64bit版のバイナリを出力し、複数のEZ-USB FX3を同時に扱うことができます。

![testapp動作画面](https://github.com/tokuden/tkusbfx3_multi64/blob/master/ezusbfx3_speed.png)

[特電Artix-7ボード](http://www.tokudenkairo.co.jp/art7/)をお持ちの方は、DLLのソースファイルを[こちら](https://www.tokudenkairo.co.jp/login2/getfile.php?target=ART764BITAPI) からダウンロードできます。

# 機能
+ EZ-USB FX3とFPGA間を最大380MByte/secの速度でRead/Write
+ 複数のEZ-USB FX3をUSB String ディスクリプタで区別してOpenする
+ SPI ROM、I2C ROM、RAMにファームウェアを転送
+ USB-JTAG
+ FPGAからの応答がない場合のタイムアウト時間の変更

# ファイルとディレクトリ
- testapp  - USBを通じてBRAMやDDR3 SDRAMに読み書きするサンプルプロジェクトです。
           複数のAritx-7ボードをUSBの「シリアル番号」で区別して開くことができます。
- tkusbfx3.h                    DLLを使うためのヘッダファイルです。
- tkusbfx3.dll                  生成されたランタイムライブラリです。64bit形式です。
- tkusbfx3.lib                  Visual C++用のインポートライブラリです

# testappのビルド方法
+ (1) testapp\testapp.vcxproj をVisual Studio 2019で開きます。
+ (2) tkusbfx3.dllとtkusbfx3.libとtkusbfx3.hを最新のものにします。
+ (3) ビルドします。

# プログラムの作成方法
[こちら](http://www.tokudenkairo.co.jp/art7/apiprog.html)のページをご覧ください。

---------------------

# Copyright 
(C)2014-2019 特殊電子回路株式会社
