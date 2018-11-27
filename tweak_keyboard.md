修改/usr/share/X11/xkb/symbols下的pc和us文件。

将Escape键和Tilde键互换。
修改pc文件：
```
default  partial alphanumeric_keys modifier_keys
xkb_symbols "pc105" {

    // key <ESC>  {	[ Escape		]	};
    key <ESC>  {	[ grave, asciitilde		]	};
    ...
    // key <CAPS> { [Caps_Lock      ]   };
    key <CAPS> {    [Control_L      ]   };
```

修改us文件：
```
default  partial alphanumeric_keys modifier_keys
xkb_symbols "basic" {

    name[Group1]= "English (US)";

    // key <TLDE> {	[     grave,	asciitilde	]	};
    key <TLDE> {	[     Escape ]	};
    ...
```

将Alt+hjkl键改为left、down、up、right键。
修改altwin文件：
```
// Meta is mapped to second level of Alt keys.
partial modifier_keys
xkb_symbols "meta_alt" {
    // key <LALT> { [ Alt_L, Meta_L ] };
    key <RALT> { type[Group1] = "TWO_LEVEL",
                 symbols[Group1] = [ Alt_R, Meta_R ] };
    modifier_map Mod1 { Alt_L, Alt_R, Meta_L, Meta_R };
//  modifier_map Mod4 {};
};
```

修改us文件：
```
key <AC06> {	[	  h,	H, Left		]	};
key <AC07> {	[	  j,	J, Down		]	};
key <AC08> {	[	  k,	K, Up		]	};
key <AC09> {	[	  l,	L, Right		]	};
key <LALT> {    [     ISO_Level3_Shift      ]   };
```

将left ctrl键改为alt键：
```
// Meta is mapped to second level of Alt keys.
partial modifier_keys
xkb_symbols "meta_alt" {
    key <LCTL> { [ Alt_L, Meta_L ] };
    // key <LALT> { [ Alt_L, Meta_L ] };
    key <RALT> { type[Group1] = "TWO_LEVEL",
                 symbols[Group1] = [ Alt_R, Meta_R ] };
    modifier_map Mod1 { Alt_L, Alt_R, Meta_L, Meta_R };
//  modifier_map Mod4 {};
};
```
