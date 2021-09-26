#Разметка кода:<br>
Кол-во регистров `0x0 - 0x2`<br>
Байт-код `0x2 - 0x7FFFFFFF`

#Байт-код:
| Код    | Параметры | Имя | Дескриптор | Описание |
| ------ | --------- | --- | ---------- | -------- |
|`0x0`|`0x1 (RX)` `0x2 (RY)`|Move Register|MR (RX, RY)|RX to RY|
|`0x1` - `0x4`| `Ox1 (RX)` `Ox2 (RY)`|MRT (RX, RY)|Move Register with Type|(LL,HH,LH,HL) bytes, RX to RY|
|`0x5`| `0x1 (RX)`|PhS (RX)|Push to Stack|RX to stack|
|`0x6`|`0x1 (RX)`|Pp (RX)|Pop to RX|Stack to RX|
|`0x7`|`0x1 (RX)`|Pk (RX)|Peek to RX|Stack to RX|
|`0x8`|`0x1 (RX)` `0x2 (RY)`|DR (RX, RY)|Dereference Register|REGY = *REGX|
|`0x9`|`0x1 (RX)` `0x2 (RY)`|RR (RX, RY)|Reference Register|REGY = (void*) REGX|
|`0xA`|`0x1 (RX)` `0x2 (TYPE)`|CTV (RX, TYPE)|Convert To Val|RX = new Value_t(RX, TYPE, false)|
|`0xB`|`0x1 (RX)` `0x2 (TYPE)`|CTCV (RX, TYPE)|Convert To Collecteble Val|RX = new Value_t(RX, TYPE, false)|
|`0xC`|`0x1 (RX)`|CFV (RX)|UnConvert Of Value|RX = RX->value|
|`0xD`|`0x1 (RX)`|CFVADV (RX)|UnConvert Of Value And Delete Value|RX = RX->value|
|`0xF` - `0x15`|`0x1 (RX)` `0x2 (RY)` `0x3 (RZ)`|MR (RX, RY, RZ)|Math Register|RZ = RX TYPE (TYPE: ADD; SUB; MUL; DIV; POW; SQRT) RY|
|`0x16`|`0x1 (RX)` `0x2 (BYTE)`|LTR1 (RX, BYTE)|Load To Register|RX = BYTE|
|`0x17`|`0x1 (RX)` `0x2 (BYTE0)` `0x3 (BYTE1)`|LTR2 (RX, BYTE0, BYTE1)|Load To Register|RX = BYTE0 &#124; (BYTE1 << 8)|
|`0x18`|`0x1 (RX)` `0x2 (BYTE0)` `0x3 (BYTE1)` `0x4 (BYTE2)` `0x5(BYTE3)`|LTR4 (RX, BYTE0, BYTE1, BYTE2, BYTE3)|Load To Register|RX = BYTE0 &#124; (BYTE1 << 8) &#124; BYTE2 << 16) &#124; (BYTE3 << 24)|
