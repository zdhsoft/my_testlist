# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['D:\\dist\\sendlist\\main.py'],
             pathex=['D:\\dist'],
             binaries=[],
             datas=[('D:\\dist\\sendlist\\importFile\\*.xlsx','importFile'),
                    ('D:\\dist\\sendlist\\result\\*.xlsx','result')],
             hiddenimports=['lib.adress','lib.myxl','cpca'],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          [],
          exclude_binaries=True,
          name='test',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=True )
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=True,
               upx=True,
               upx_exclude=[],
               name='test')
