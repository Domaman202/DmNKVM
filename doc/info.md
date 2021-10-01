# Разметка кода:<br>
Кол-во регистров `0x0 - 0x2`<br>
Байт-код `0x2 - 0x7FFFFFFF`

# Байт-код:
| Код    | Параметры | Дескриптор | Имя | Описание |
| ------ | --------- | ---------- | --- | -------- |
|`0x0`||NOP|No Operation|Empty Opcode|
|`0x1`|`0x1 (RX)` `0x2 (RY)`|MR (RX, RY)|Move Register|RX to RY|
|`0x2`<br><=><br>`0x5`| `Ox1 (RX)` `Ox2 (RY)`|MRT (RX, RY)|Move Register with Type|(LL,HH,LH,HL) bytes, RX to RY|
|`0x6`| `0x1 (RX)`|PS (RX)|Push to Stack|RX to stack|
|`0x7`|`0x1 (RX)`|PP (RX)|Pop to register|Stack to RX|
|`0x8`|`0x1 (RX)`|PK (RX)|Peek to register|Stack to RX|
|`0x9`|`0x1 (RX)` `0x2 (RY)`|DR (RX, RY)|Dereference Register|REGY = &#42;(void&#42;&#42;) REGX|
|`0xA`|`0x1 (RX)` `0x2 (RY)`|RR (RX, RY)|Reference Register|REGY = (void&#42;&#42;) REGX|
|`0xB`|`0x1 (RX)` `0x2 (TYPE)`|CTV (RX, TYPE)|Convert To Val|RX = new Value_t(RX, TYPE, false)|
|`0xC`|`0x1 (RX)` `0x2 (TYPE)`|CTCV (RX, TYPE)|Convert To Collecteble Val|RX = new Value_t(RX, TYPE, true)|
|`0xD`|`0x1 (RX)`|UCOV (RX)|UnConvert Of Val|RX = RX->value|
|`0xE`|`0x1 (RX)`|UCOVD (RX)|UnConvert Of Val and Delete val|RX = RX->value|
|`0xF`<br><=><br>`0x14`|`0x1 (RX)` `0x2 (RY)` `0x3 (RZ)` `0x4 (BYTE0)`|MTR (RX, RY, RZ, BYTE0)|MaTh Register|RZ = (BYTE0) RX TYPE (TYPE: ADD; SUB; MUL; DIV; POW; SQRT) (BYTE0) RY|
|`0x15`|`0x1 (RX)` `0x2 (BYTE)`|LTR1 (RX, BYTE)|Load To Register|RX = BYTE|
|`0x16`|`0x1 (RX)` `0x2 (BYTE0)` `0x3 (BYTE1)`|LTR2 (RX, BYTE0, BYTE1)|Load To Register|RX = BYTE0 &#124; (BYTE1 << 8)|
|`0x17`|`0x1 (RX)` `0x2 (BYTE0)` `0x3 (BYTE1)` `0x4 (BYTE2)` `0x5(BYTE3)`|LTR4 (RX, BYTE0, BYTE1, BYTE2, BYTE3)|Load To Register|RX = BYTE0 &#124; (BYTE1 << 8) &#124; BYTE2 << 16) &#124; (BYTE3 << 24)|
|`0x18`|`0x1 (RX)`|C (RX)|Call|RX()|
|`0x19`|`0x1 (RX)`|CWC (RX)|Call With Context|RX(this (`vm`), RX (`execution context`)) 
|`0x1A`||R|Return|return
|`0x1B`|`0x1 (RX)`|GT (RX)|Go To|Setting code ptr to RX|
|`0x1C`|`0x1 (RX)` `0x2 (RY)`|CC0 (RX, RY)|Create Call|Create a call with RX (object) and RY (method)
|`0x1D`|`0x1 (RA)` `0x2 (RB)` `0x3 (RC)` `0x4 (RD)` `0x5 (RE)` `0x6 (RF)`|CC1 (RA, RB, RC, RD, RE, RF)|Create call|Creating a full call struct|
|`0x1E`|`0x1 (RA)` `0x2 (RB)` `0x3 (RC)` `0x4 (RD)` `0x5 (RE)`|CEC (RA, RB, RC, RD, RE)|Create Execution Context|Creating execution context|
|`0x1F`|`0x1 (RX)` `0x2 (BYTE0)`|SGA (RX, BYTE0)|Static Get Argument|Getting argument №BYTE0 to RX|
|`0x20`|`0x1 (RX)` `0x2 (RY)`|DGA (RX, RY)|Dynamic Get Argument|Getting argument №RX to RY|
|`0x21`|`0x1 (RX)` `0x2 (RY)`|RS (RX, RY)|Register String|Registring string in string RX storage and setting RY to string id|
|`0x22`|`0x1 (RX)` `0x2 (RY)`|GS (RX, RY)|Get String|Getting string in string storage with id RX to RY|
|`0x23`|`0x1 (RX)` `0x2 (RY)`|SR (RX, RY)|Swap Registers|Swapping RX and RY|
|`0x24`|`0x1 (RX)` `0x3 (BYTES)`|LS (RX), (BYTES)|Load String|Loading string with BYTES to RX|
|`0x25`|`0x1 (RX)`|IRC (RX)|Increment References|Inc refs of val|
|`0x26`|`0x1 (RX)`|DRC (RX)|Decrement References|Dec refs of val|
