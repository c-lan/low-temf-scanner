# Scanner

Scanner supports following modes: 16CH x 2W, 8CH x 4W.
16CH x 2W is also known as combined mode. It uses an additional relay that shorts card A and B outputs.
Channels are numbered from 1 to 16.
4W channels are referenced by numbers 1-8. If 4W channel is enabled, operations on corresponding 9-16 channels are not possible.

# Controller support

STM32F103 based Blue Pill board is being used as a controller. In the future it will be replaced by a universal controller board with USB, ethernet and more GPIO. Powering by USB is recommended to minimize thermal dissipation.

Pinout:

- USB- `PA11`, USB+ `PA12`
- SCL `PB8`, SDA `PB9`

# Commands

`ROUTe:CLOSe <channel>`  
`ROUTe:CLOSe:STATe?`

Connect a channel. In 2W mode there channels 1-16 are available. In 4W mode channels 1-8 are available.
Only one channel can be closed at the same time. Closing one channel opens the one that was previously closed.
Querying returns a channel number or empty string.

`ROUTe:OPEN:ALL`

Opens currently closed channel.

`ROUTe:CHANnel:FWIRe {`**`OFF`**` | ON }`  
`ROUTe:CHANnel:FWIRe?`

Enable or disable 4W mode for all channels. Changing mode opens all channels.

`ROUTe:CONNection:SEQuence { BBM | MBB | `**`DEF`**`}`  
`ROUTe:CONNection:SEQuence?`

Set sequence of closing and opening operations - break before make (default) or make before break.

# TODO
- Scanning channels in sequence
- Trigger in, trigger out modes
- Advanced trigger configuration for standalone operation
- Counting relay switching cycles, relay cleaning by fast switching
- Independent 2x8x2W mode. Totally arbitrary connection mode.
