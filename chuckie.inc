;==========================================================
; Version 1
;
; - Joystick routine changed for AtoMMC v2.9
;==========================================================

;
; Code equates
;

clearmode     equ $f0
green         equ $c0
yellow        equ $c0
blue          equ $c0
red           equ $c0

waitkey       equ $fe71

;------------------------------------------------
; Used variables $00-$8F
;------------------------------------------------

L001B       equ $001B    ; Joystick flag
L001C       equ $001C    ; Timer

L001D       equ $001D    ; Time digit 3
L001E       equ $001E    ; Time digit 2
L001F       equ $001F    ; Time digit 1

L0020       equ $0020    ; Saved lives player 1
L0021       equ $0021    ; Saved lives player 2
L0022       equ $0022    ; Saved lives player 3
L0023       equ $0023    ; Saved lives player 4
L0024       equ $0024    ; Saved level player 1
L0025       equ $0025    ; Saved level player 2
L0026       equ $0026    ; Saved level player 3
L0027       equ $0027    ; Saved level player 4

L0028       equ $0028    ; Score 8 bytes

L0030       equ $0030    ; X-pos duck
L0031       equ $0031    ; Y-pos duck
L0032       equ $0032    ; X-dir duck
L0033       equ $0033    ; Y-dir duck
L0034       equ $0034    ; Duck spritenr
L0035       equ $0035    ; Duck flag
                         ;  Level 0-7 Duck in cage
                         ;  Level 8-.. Duck outside cage
L0036       equ $0036    ; Temp bird delay ticker 

L0037       equ $0037    ; Initial bird delay ticker
L0038       equ $0038    ; Temp duck deley ticker
L0039       equ $0039    ; Egg on screen counter

L003A       equ $003A    ; Bonus digit 4
L003B       equ $003B    ; Bonus digit 3
L003C       equ $003C    ; Bonus digit 2
L003D       equ $003D    ; Bonus digit 1, digit 0 always 0

L003E       equ $003E

L003F       equ $003F    ; Position lives left player

L0040       equ $0040    ; X-pos man
L0041       equ $0041    ; Y-pos man
L0042       equ $0042    ; X-pos man in bytes
L0043       equ $0043    ; Y-pos man in bytes
L0044       equ $0044    ; X-pos man mod 8 (0-7)
L0045       equ $0045    ; Y-pos man mod 8 (0-7)
L0046       equ $0046    ; Man x-dir
L0047       equ $0047    ; Man y-dir
L0048       equ $0048    ; Current man sprite nr
L0049       equ $0049    ; Movement man
                         ;  0 = Horizontal
                         ;  1 = Climbing ladder
                         ;  2 = Jump
                         ;  3 = Fall
                         ;  4 = Elevator
L004A       equ $004A    ; Tone jump man
L004B       equ $004B    ; Current y-dir man
L004C       equ $004C    ; Current x-dir man

;------------------------------------------------
;              Hens  Duck  Skip Levelnibble high  
;------------------------------------------------
; Levels  1- 8: 2-4   no    7      0
; Levels  9-16:  0   yes    7      1
; Levels 17-24: 2-4  yes    7      2
; Levels 25-32: 2-5  yes    7      3
; Levels 33   : 2-5  yes    5      4
;------------------------------------------------

L004D       equ $004D    ; Levelnibble high

L004E       equ $004E    ; Pointer to savedata at $5xx player

L004F       equ $004F

L0050       equ $0050    ; Levelnr??

L0051       equ $0051    ; Leveldata pointer
L0052       equ $0052

L0053       equ $0053    ; Nr of walls
L0054       equ $0054    ; Nr of ladders
L0055       equ $0055    ; Elevator flag
L0056       equ $0056    ; Nr of seed
L0057       equ $0057    ; Nr of birds
L0058       equ $0058    ; x-pos elevator 
L0059       equ $0059    ; y-pos elevator low 
L005A       equ $005A    ; y-pos elevator high
L005B       equ $005B    ; Elevator flag 0=$59, $FF=$5A

L005C       equ $005C    ; Levelnibble low
L005D       equ $005D    ; Current player nr
L005E       equ $005E    ; Max nr players (4)

L005F       equ $005F    ; Max nr players (4)
L0060       equ $0060

L0061       equ $0061    ; Right key
L0062       equ $0062    ; Left key
L0063       equ $0063    ; Down key
L0064       equ $0064    ; Up key
L0065       equ $0065    ; Jump key

L0066       equ $0066    ; Calc number
L0067       equ $0067    ; Calc number
L0068       equ $0068    ; Calc number
L0069       equ $0069    ; Calc number

L0070       equ $0070    ; Screen pointer
L0071       equ $0071

L0072       equ $0072
L0073       equ $0073
L0074       equ $0074
L0075       equ $0075

L0076       equ $0076    ; Sprite pointer
L0077       equ $0077

L0078       equ $0078    ; Sprite height counter
L0079       equ $0079
L007A       equ $007A

L007B       equ $007B   ; Background buffer pointer
L007C       equ $007C

L007F       equ $007F   ; Color byte

L0080       equ $0080   ; Key pressed flag 1,2,4,8,16
L0081       equ $0081   ; Pixel shift backup register
L0082       equ $0082   ; Screen databyte
L0083       equ $0083   ; Sprite databyte pixel shift counter
L0084       equ $0084   ; Sprite databyte
L0087       equ $0087   ; Sprite width in bytes

L0088       equ $0088   ; Bird pointer
L0089       equ $0089   ; Level datapointer
L008A       equ $008A   ; Different counters
L008B       equ $008B
L008C       equ $008C
L008D       equ $008D
L008E       equ $008E
L008F       equ $008F

;------------------------------------------------
; Bird data (5x)
;
; $400,$401,$402,$403,$404 X-pos pixels
; $405,$406,$407,$408,$409 Y-pos pixels
; $40a,$40b,$40c,$40d,$40e X-pos bytes
; $40f,$410,$411,$412,$413 Y-pos bytes
; $414,$415,$416,$417,$418 Sprite nr
; $419,$41a,$41b,$41c,$41d Sprite nr 
; $41e,$41f,$420,$421,$422 Sprite nr 

;------------------------------------------------

L0400       equ $0400
L0405       equ $0405
L040A       equ $040A
L040F       equ $040F
L0414       equ $0414
L0419       equ $0419
L041E       equ $041E

;------------------------------------------------
; Save player data
;
; $500,$540,$580,$5C0 (8) Saved player score
; $508,$548,$588,$5C8 (4) Saved player bonus
; $50C,$54C,$58C,$5CC (4) Free
; $510,$550,$590,$5D0 (16) Eggs flag $ff=gone
; $520,$560,$5A0,$5E0 (16) Seed flag $ff=gone
;------------------------------------------------

L0500       equ $0500
L0508       equ L0500+8
L0509       equ L0500+9
L050A       equ L0500+$A
L050B       equ L0500+$B
L0510       equ L0500+$10
L0520       equ L0500+$20

L0600       equ $0600  ; Screencopy upper half
L0700       equ $0700  ; Screencopy lower half

L0900       equ $0900  ; Relocation address code
L0903       equ $0903
L094F       equ $094F
L0976       equ $0976
L09CF       equ $09CF
L0A00       equ $0A00
L0A10       equ $0A10
L0A16       equ $0A16
L0A6C       equ $0A6C
L0A6F       equ $0A6F
L0A72       equ $0A72
L0A9C       equ $0A9C
L0AA9       equ $0AA9
L0AB8       equ $0AB8
L0AC7       equ $0AC7
L0B00       equ $0B00
L0B06       equ $0B06
L0B44       equ $0B44
L0B9C       equ $0B9C
L0BE4       equ $0BE4
L0C00       equ $0C00
L0C04       equ $0C04
L0C0B       equ $0C0B
L0C11       equ $0C11
L0C12       equ $0C12
L0C16       equ $0C16
L0C3E       equ $0C3E
L0C80       equ $0C80
L0C9C       equ $0C9C
L0CA4       equ $0CA4
L0CA6       equ $0CA6
L0CAC       equ $0CAC
L0CC0       equ $0CC0
L0CD0       equ $0CD0
L0D00       equ $0D00
L0D07       equ $0D07
L0D3E       equ $0D3E
L0DB2       equ $0DB2
L0E00       equ $0E00
L0E02       equ $0E02
L0E0D       equ $0E0D
L0E12       equ $0E12
L0E20       equ $0E20
L0E4B       equ $0E4B
L0EDC       equ $0EDC
L0E70       equ $0E70
L0F00       equ $0F00
L0F02       equ $0F02
L0F0C       equ $0F0C
L0F6C       equ $0F6C
L0FE8       equ $0FE8
L1000       equ $1000
L1001       equ $1001
L1002       equ $1002
L1006       equ $1006
L1010       equ $1010
L1011       equ $1011
L1012       equ $1012
L1015       equ $1015
L1017       equ $1017
L1018       equ $1018
L10BB       equ $10BB
L1072       equ $1072

L3200       equ $3200
L3300       equ $3300
L3400       equ $3400
L3500       equ $3500
L3600       equ $3600
L3700       equ $3700
L3800       equ $3800
OSWRCH      equ $FFEE
OSWORD      equ $FFF1
OSBYTE      equ $FFF4

;
; Start of code
;
;            *equ $1100
;

	jmp program_entry

;------------------------------------------------
; Sprite lookup table
;------------------------------------------------
sprites:
         .byte $96,$18,$00,$36       ; Sprite 0   - Not used
         .byte $08,$08,<L1200,>L1200 ; Sprite 1   - Wall
         .byte $08,$08,<L1208,>L1208 ; Sprite 2   - Ladder
         .byte $08,$08,<L1210,>L1210 ; Sprite 3   - Egg
         .byte $08,$08,<L1218,>L1218 ; Sprite 4   - Seed
         .byte $10,$04,<L1220,>L1220 ; Sprite 5   - Elevator
         .byte $08,$10,<L1228,>L1228 ; Sprite 6   - Man stand right
         .byte $08,$10,<L1238,>L1238 ; Sprite 7   - Man walk right1
         .byte $08,$10,<L1248,>L1248 ; Sprite 8   - Man walk right2
         .byte $08,$10,<L1258,>L1258 ; Sprite 9   - Man stand left
         .byte $08,$10,<L1268,>L1268 ; Sprite $a  - Man walk left1
         .byte $08,$10,<L1278,>L1278 ; Sprite $b  - Man walk left2
         .byte $08,$10,<L1288,>L1288 ; Sprite $c  - Man stand climb
         .byte $08,$12,<L1298,>L1298 ; Sprite $d  - Man climb1
         .byte $08,$12,<L12AA,>L12AA ; Sprite $e  - Man climb2
         .byte $10,$18,<L12BC,>L12BC ; Sprite $f  - Duck right1
         .byte $10,$18,<L12EC,>L12EC ; Sprite $10 - Duck right2
         .byte $10,$18,<L131C,>L131C ; Sprite $11 - Duck left1
         .byte $10,$18,<L134C,>L134C ; Sprite $12 - Duck left2
         .byte $18,$30,<L137C,>L137C ; Sprite $13 - Duck cage right
         .byte $18,$30,<L140C,>L140C ; Sprite $14 - Duck cage empty
         .byte $08,$14,<L149C,>L149C ; Sprite $15 - Bird stand right
         .byte $08,$14,<L14B0,>L14B0 ; Sprite $16 - Bird walk right
         .byte $08,$14,<L14C4,>L14C4 ; Sprite $17 - Bird stand left
         .byte $08,$14,<L14D8,>L14D8 ; Sprite $18 - Bird walk left
         .byte $08,$14,<L14EC,>L14EC ; Sprite $19 - Bird climb1
         .byte $08,$16,<L1500,>L1500 ; Sprite $1a - Bird climb2
         .byte $10,$14,<L1516,>L1516 ; Sprite $1b - Bird eat right1
         .byte $10,$14,<L153E,>L153E ; Sprite $1c - Bird eat right2
         .byte $10,$14,<L1566,>L1566 ; Sprite $1d - Bird eat left1
         .byte $10,$14,<L158E,>L158E ; Sprite $1e - Bird eat left2
         .byte $08,$07,<L15B6,>L15B6 ; Sprite $1f - 0
         .byte $08,$07,<L15BD,>L15BD ; Sprite $20 - 1
         .byte $08,$07,<L15C4,>L15C4 ; Sprite $21 - 2
         .byte $08,$07,<L15CB,>L15CB ; Sprite $22 - 3
         .byte $08,$07,<L15D2,>L15D2 ; Sprite $23 - 4
         .byte $08,$07,<L15D9,>L15D9 ; Sprite $24 - 5
         .byte $08,$07,<L15E0,>L15E0 ; Sprite $25 - 6
         .byte $08,$07,<L15E7,>L15E7 ; Sprite $26 - 7
         .byte $08,$07,<L15EE,>L15EE ; Sprite $27 - 8
         .byte $08,$07,<L15F5,>L15F5 ; Sprite $28 - 9
         .byte $18,$09,<L15FC,>L15FC ; Sprite $29 - SCORE
         .byte $20,$09,<L1617,>L1617 ; Sprite $2a - SPACE 8x
         .byte $20,$09,<L163B,>L163B ; Sprite $2b - PLAYER
         .byte $20,$09,<L165F,>L165F ; Sprite $2c - LEVEL + spaces
         .byte $28,$09,<L168C,>L168C ; Sprite $2d - BONUS + spaces
         .byte $20,$09,<L16C2,>L16C2 ; Sprite $2e - TIME + spaces
         .byte $08,$03,<L16EF,>L16EF ; Sprite $2f - Lifes icon
         .byte $10,$18,<L16F2,>L16F2 ; Sprite $30 - C
         .byte $10,$18,<L172E,>L172E ; Sprite $31 - H
         .byte $10,$18,<L176A,>L176A ; Sprite $32 - U
         .byte $10,$18,<L17A6,>L17A6 ; Sprite $33 - K
         .byte $08,$18,<L17E2,>L17E2 ; Sprite $34 - I
         .byte $10,$18,<L181E,>L181E ; Sprite $35 - E
         .byte $10,$18,<L185A,>L185A ; Sprite $36 - G

         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00

L1200:   .byte $fb,$00,$bf,$00,$ef,$00,$00,$00 ; Wall
L1208:   .byte $42,$42,$42,$42,$7e,$42,$42,$42 ; Ladder
L1210:   .byte $00,$38,$6c,$5e,$7e,$7c,$38,$00 ; Egg
L1218:   .byte $00,$00,$00,$08,$14,$2a,$55,$00 ; Seed
L1220:   .byte $1f,$f8,$1f,$f8,$1b,$d8,$11,$88 ; Elevator
L1228:   .byte $18,$3c,$ff,$34,$3c,$10,$18,$3c ; Man stand right
         .byte $6e,$6e,$6e,$6e,$3c,$18,$10,$18
L1238:   .byte $18,$3c,$ff,$34,$3c,$10,$18,$3c ; Man walk right1
         .byte $6e,$6e,$76,$76,$3c,$38,$4a,$24
L1248:   .byte $18,$3c,$ff,$34,$3c,$10,$18,$3c ; Man walk right2
         .byte $6e,$6e,$5e,$5e,$3c,$38,$4a,$24
L1258:   .byte $18,$3c,$ff,$2c,$3c,$08,$18,$3c ; Man stand left
         .byte $76,$76,$76,$76,$3c,$18,$08,$18
L1268:   .byte $18,$3c,$ff,$2c,$3c,$08,$18,$3c ; Man walk left1
         .byte $76,$76,$6e,$6e,$3c,$1c,$52,$24
L1278:   .byte $18,$3c,$ff,$2c,$3c,$08,$18,$3c ; Man walk left2
         .byte $76,$76,$7a,$7a,$3c,$1c,$52,$24
L1288:   .byte $18,$3c,$ff,$3c,$3c,$18,$18,$bd ; Man climb
         .byte $ff,$7e,$7e,$7e,$3c,$24,$24,$66
L1298:   .byte $18,$3c,$ff,$3c,$3d,$19,$19,$3d ; Man climb1
         .byte $ff,$fe,$fe,$fe,$bc,$3e,$20,$20
         .byte $20,$60
L12AA:   .byte $18,$3c,$ff,$3c,$bc,$98,$98,$bc ; Man climb2
         .byte $ff,$7f,$7f,$7f,$3d,$7c,$04,$04
         .byte $04,$06
L12BC:   .byte $00,$70,$00,$f8                 ; Duck right1
         .byte $01,$e8,$01,$ef,$01,$ff,$01,$f8
         .byte $00,$f0,$00,$e0,$00,$60,$0e,$70
         .byte $1f,$70,$3f,$f8,$7f,$f8,$ff,$78
         .byte $ff,$b8,$bf,$bc,$bf,$bc,$df,$bc
         .byte $6f,$7c,$76,$fc,$39,$f8,$1f,$f8
         .byte $0f,$f0,$03,$e0
L12EC:   .byte $00,$70,$00,$f9                 ; Duck right2
         .byte $01,$ea,$01,$ec,$01,$fc,$01,$fa
         .byte $00,$f1,$00,$e0,$00,$60,$0e,$70
         .byte $1f,$70,$3f,$f8,$71,$f8,$ee,$78
         .byte $df,$b8,$bf,$fc,$ff,$fc,$ff,$fc
         .byte $7f,$fc,$7f,$fc,$3f,$f8,$1f,$f8
         .byte $0f,$f0,$03,$e0
L131C:   .byte $0e,$00,$1f,$00                 ; Duck left1
         .byte $17,$80,$f7,$80,$ff,$80,$1f,$80
         .byte $0f,$00,$07,$00,$06,$00,$0e,$70
         .byte $0e,$f8,$1f,$fc,$1f,$fe,$1e,$ff
         .byte $1d,$ff,$3d,$fd,$3d,$fd,$3d,$fb
         .byte $3e,$f6,$3f,$6e,$1f,$9c,$1f,$f8
         .byte $0f,$f0,$07,$c0
L134C:   .byte $0e,$00,$9f,$00                 ; Duck left2
         .byte $57,$80,$37,$80,$3f,$80,$5f,$80
         .byte $8f,$00,$07,$00,$06,$00,$0e,$70
         .byte $0e,$f8,$1f,$fc,$1f,$8e,$1e,$77
         .byte $1d,$fb,$3f,$fd,$3f,$ff,$3f,$ff
         .byte $3f,$fe,$3f,$fe,$1f,$fc,$1f,$f8
         .byte $0f,$f0,$07,$c0
L137C:   .byte $00,$38,$00,$00                 ; Duck cage right
         .byte $44,$00,$00,$44,$00,$00,$44,$00
         .byte $00,$38,$00,$00,$10,$00,$00,$fe
         .byte $00,$03,$7d,$80,$0c,$d6,$60,$11
         .byte $55,$10,$22,$54,$88,$24,$92,$48
         .byte $44,$92,$44,$48,$92,$24,$88,$92
         .byte $22,$89,$11,$22,$d1,$10,$16,$b1
         .byte $10,$0a,$99,$00,$02,$97,$00,$02
         .byte $91,$e0,$02,$91,$00,$02,$91,$10
         .byte $02,$91,$10,$12,$91,$10,$12,$91
         .byte $10,$12,$90,$00,$12,$90,$00,$12
         .byte $90,$00,$12,$d0,$00,$16,$b0,$00
         .byte $1a,$90,$00,$32,$90,$00,$12,$90
         .byte $00,$12,$90,$00,$12,$90,$00,$12
         .byte $90,$00,$12,$90,$00,$12,$91,$00
         .byte $12,$91,$01,$12,$91,$11,$12,$91
         .byte $11,$12,$d1,$11,$12,$51,$11,$14
         .byte $31,$11,$18,$19,$11,$30,$07,$11
         .byte $c0,$00,$fe,$00
L140C:   .byte $00,$38,$00,$00                 ; Duck cage empty
         .byte $44,$00,$00,$44,$00,$00,$44,$00
         .byte $00,$38,$00,$00,$10,$00,$00,$fe
         .byte $00,$03,$7d,$80,$0c,$d6,$60,$11
         .byte $55,$10,$22,$54,$88,$24,$92,$48
         .byte $44,$92,$44,$48,$92,$24,$88,$92
         .byte $22,$89,$11,$22,$d1,$11,$16,$b1
         .byte $11,$1a,$99,$11,$32,$97,$11,$d2
         .byte $91,$ff,$12,$91,$11,$12,$91,$11
         .byte $12,$91,$11,$12,$91,$11,$12,$91
         .byte $11,$12,$91,$11,$12,$91,$11,$12
         .byte $91,$11,$12,$d1,$11,$16,$b1,$11
         .byte $1a,$99,$11,$32,$97,$11,$d2,$91
         .byte $ff,$12,$91,$11,$12,$91,$11,$12
         .byte $91,$11,$12,$91,$11,$12,$91,$11
         .byte $12,$91,$11,$12,$91,$11,$12,$91
         .byte $11,$12,$d1,$11,$12,$51,$11,$14
         .byte $31,$11,$18,$19,$11,$30,$07,$11
         .byte $c0,$00,$fe,$00
L149C:   .byte $0c,$1b,$1c,$08                 ; Bird stand right
         .byte $08,$04,$04,$02,$32,$7b,$7f,$7f
         .byte $7f,$3e,$18,$10,$10,$10,$10,$18
L14B0:   .byte $0d,$1a,$1d,$08,$08,$04,$04,$02 ; Bird walk right
         .byte $32,$7b,$7f,$7f,$7f,$3e,$18,$28
         .byte $28,$44,$45,$22
L14C4:   .byte $30,$d8,$38,$10                 ; Bird stand left
         .byte $10,$20,$20,$40,$4c,$de,$fe,$fe
         .byte $fe,$7c,$18,$08,$08,$08,$08,$18
L14D8:   .byte $b0,$58,$b8,$10,$10,$20,$20,$40 ; Bird walk left
         .byte $4c,$de,$fe,$fe,$fe,$7c,$18,$14
         .byte $14,$22,$a2,$44
L14EC:   .byte $18,$3c,$3c,$3c                 ; Bird climb1
         .byte $18,$18,$18,$3c,$7e,$7e,$7e,$7e
         .byte $7e,$3c,$3c,$24,$24,$26,$20,$60
L1500:   .byte $18,$3c,$3c,$3c,$18,$18,$18,$3c ; Bird climb2
         .byte $7e,$7e,$7e,$7e,$7e,$3c,$3c,$24
         .byte $24,$64,$04,$04,$04,$06
L1516:   .byte $00,$00                         ; Bird eat right1
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$38,$30,$28,$78,$78
         .byte $7c,$c4,$7f,$c2,$7f,$80,$3f,$00
         .byte $3f,$00,$1f,$00,$16,$00,$10,$00
         .byte $10,$00,$10,$00,$18,$00
L153E:   .byte $00,$00                         ; Bird eat right2
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00,$30,$00,$78,$00
         .byte $7c,$00,$7e,$00,$7f,$f8,$3f,$f4
         .byte $3f,$14,$1f,$08,$16,$08,$10,$08
         .byte $10,$00,$10,$00,$18,$00
L1566:   .byte $00,$00                         ; Bird eat left1
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$1c,$00,$14,$0c,$1e,$1e
         .byte $23,$3e,$43,$fe,$01,$fe,$00,$fc
         .byte $00,$fc,$00,$f8,$00,$68,$00,$08
         .byte $00,$08,$00,$08,$00,$18
L158E:   .byte $00,$00                         ; Bird eat left2
         .byte $00,$00,$00,$00,$00,$00,$00,$00
         .byte $00,$00,$00,$00,$00,$0c,$00,$1e
         .byte $00,$3e,$00,$7e,$1f,$fe,$2f,$fc
         .byte $28,$fc,$10,$f8,$10,$68,$10,$08
         .byte $00,$08,$00,$08,$00,$18
L15B6:   .byte $40,$a0,$a0,$a0,$a0,$a0,$40     ; 0
L15BD:   .byte $40,$c0,$40,$40,$40,$40,$e0     ; 1
L15C4:   .byte $40,$a0,$20,$20,$40,$80,$e0     ; 2
L15CB:   .byte $40,$a0,$20,$40,$20,$a0,$40     ; 3
L15D2:   .byte $20,$40,$80,$a0,$e0,$20,$20     ; 4
L15D9:   .byte $e0,$80,$80,$c0,$20,$a0,$40     ; 5
L15E0:   .byte $20,$40,$80,$c0,$a0,$a0,$40     ; 6
L15E7:   .byte $e0,$20,$20,$40,$80,$80,$80     ; 7
L15EE:   .byte $40,$a0,$a0,$40,$a0,$a0,$40     ; 8
L15F5:   .byte $40,$a0,$a0,$60,$20,$40,$80     ; 9
L15FC:   .byte $ff,$ff,$f8                     ; SCORE
         .byte $dd,$d9,$88
         .byte $aa,$aa,$b8
         .byte $bb,$aa,$b8
         .byte $db,$a9,$98
         .byte $eb,$aa,$b8
         .byte $aa,$aa,$b8
         .byte $dd,$da,$88
         .byte $ff,$ff,$f8
L1617:   .byte $ff                             ; SPACE 8x
         .byte $ff,$ff,$80,$ff,$ff,$ff,$80,$ff
         .byte $ff,$ff,$80,$ff,$ff,$ff,$80,$ff
         .byte $ff,$ff,$80,$ff,$ff,$ff,$80,$ff
         .byte $ff,$ff,$80,$ff,$ff,$ff,$80,$ff
         .byte $ff,$ff,$80
L163B:   .byte $ff,$ff,$ff,$f8                 ; PLAYER
         .byte $9b,$da,$89,$f8
         .byte $ab,$aa,$ba,$f8
         .byte $ab,$aa,$ba,$f8
         .byte $9b,$8d,$99,$f8
         .byte $bb,$ad,$ba,$f8
         .byte $bb,$ad,$ba,$f8
         .byte $b8,$ad,$8a,$f8
         .byte $ff,$ff,$ff,$f8
L165F:   .byte $ff,$ff,$ff,$f8                 ; LEVEL + spaces
         .byte $b8,$a8,$bf,$f8
         .byte $bb,$ab,$bf,$f8
         .byte $b9,$a9,$bf,$f8
         .byte $bb,$ab,$bf,$f8
         .byte $bb,$ab,$bf,$f8
         .byte $bb,$db,$bf,$f8
         .byte $88,$d8,$8f,$f8
         .byte $ff,$ff,$ff,$f8 
L168C:   .byte $ff,$ff,$ff,$ff,$fc            ; BONUS + spaces
         .byte $98,$b5,$6f,$ff,$fc
         .byte $aa,$95,$57,$ff,$fc
         .byte $aa,$95,$5f,$ff,$fc
         .byte $9a,$a5,$6f,$ff,$fc
         .byte $aa,$a5,$77,$ff,$fc
         .byte $aa,$b5,$57,$ff,$fc
         .byte $98,$b4,$6f,$ff,$fc
         .byte $ff,$ff,$ff,$ff,$fc
L16C2:   .byte $ff,$ff,$ff,$f8                ; TIME + spaces
         .byte $8a,$e8,$ff,$f8
         .byte $da,$4b,$ff,$f8
         .byte $da,$ab,$ff,$f8
         .byte $da,$e9,$ff,$f8
         .byte $da,$eb,$ff,$f8
         .byte $da,$eb,$ff,$f8
         .byte $da,$e8,$ff,$f8
         .byte $ff,$ff,$ff,$f8
L16EF:   .byte $40,$e0,$00                     ; Lifes icon
L16F2:
	.byte $3f,$c0  ; 0011111111000000   Letter C
	.byte $7f,$e0  ; 0111111111100000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $f9,$f0  ; 1111100111110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$60  ; 1111000001100000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$60  ; 1111000001100000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f9,$f0  ; 1111100111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $7f,$e0  ; 0111111111100000
	.byte $3f,$c0  ; 0011111111000000

L172E:
	.byte $60,$c0  ; 0110000011000000   Letter H
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$e0  ; 1111111111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$e0  ; 1111000111100000
	.byte $60,$c0  ; 0110000011000000

L176A:
	.byte $60,$60  ; 0110000001100000   Letter U
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f9,$f0  ; 1111100111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $7f,$e0  ; 0111111111100000
	.byte $3f,$c0  ; 0011111111000000

L17A6:
	.byte $60,$60  ; 0110000001100000   Letter K
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f1,$f0  ; 1111000111110000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$c0  ; 1111000111000000
	.byte $f3,$c0  ; 1111001111000000
	.byte $f3,$80  ; 1111001110000000
	.byte $f7,$80  ; 1111011110000000
	.byte $ff,$00  ; 1111111100000000
	.byte $ff,$00  ; 1111111100000000
	.byte $fe,$00  ; 1111111000000000
	.byte $fe,$00  ; 1111111000000000
	.byte $ff,$00  ; 1111111100000000
	.byte $ff,$00  ; 1111111100000000
	.byte $f7,$80  ; 1111011110000000
	.byte $f3,$80  ; 1111001110000000
	.byte $f3,$c0  ; 1111001111000000
	.byte $f1,$c0  ; 1111000111000000
	.byte $f1,$e0  ; 1111000111100000
	.byte $f1,$f0  ; 1111000111110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $60,$60  ; 0110000001100000

L17E2:
	.byte $60  ; 01100000   Letter I
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $f0  ; 11110000
	.byte $60  ; 01100000

L181E:
	.byte $3f,$e0  ; 0011111111100000   Letter E
	.byte $7f,$f0  ; 0111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$e0  ; 1111111111100000
	.byte $f8,$00  ; 1111100000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $ff,$80  ; 1111111110000000
	.byte $ff,$c0  ; 1111111111000000
	.byte $ff,$c0  ; 1111111111000000
	.byte $ff,$80  ; 1111111110000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f8,$00  ; 1111100000000000
	.byte $ff,$e0  ; 1111111111100000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $7f,$f0  ; 0111111111110000
	.byte $3f,$e0  ; 0011111111100000

L185A:
	.byte $3f,$c0  ; 0011111111000000   Letter G
	.byte $7f,$e0  ; 0111111111100000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $f9,$f0  ; 1111100111110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$60  ; 1111000001100000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f0,$00  ; 1111000000000000
	.byte $f3,$e0  ; 1111001111100000
	.byte $f3,$f0  ; 1111001111110000
	.byte $f1,$f0  ; 1111000111110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f0,$f0  ; 1111000011110000
	.byte $f9,$f0  ; 1111100111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $ff,$f0  ; 1111111111110000
	.byte $7f,$e0  ; 0111111111100000
	.byte $3f,$c0  ; 0011111111000000
L1886:   .byte $7f,$7c,$7f,$fc
         .byte $3f,$fc,$3f,$fc,$1f,$fc,$1f,$f8
         .byte $0f,$f8,$03,$f0

;------------------------------------------------

L1896:   .byte $51,$33,$34,$35,$2e,$38,$2e,$3d,$2e,$80
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$2e,$57,$45,$54,$37,$49,$39,$30,$2e,$83
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$31,$32,$44,$52,$36,$55,$4f,$50,$2e,$82
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$85,$41,$58,$46,$59,$4a,$4b,$2e,$2a,$87
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$2e,$53,$43,$47,$48,$4e,$4c,$2b,$2e,$88
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$2e,$5a,$89,$56,$42,$4d,$3c,$3e,$3f,$86
         .byte $2e,$2e,$2e,$2e,$2e,$2e,$84,$2e,$2e,$2e,$2e,$2e,$2e,$2e,$2e,$81
         .byte $0d,$ff 

;------------------------------------------------
; Plot sprite
; - Screen address in $70/$71
; - Sprite address in $76/$77
; - $81 Pixel shift horizontal
; - $82 Shifted sprite databyte
; - $83 Line counter in characterblock
; - $84 Sprite databyte
; - $87 Sprite width in bytes
;------------------------------------------------

L1902:
            lda L0073              ; Pixel shift horizontal
            sta L0081

            ldy #$00

            lda L007A              ; Sprite width in bytes
            sta L0087

            ldx #$00
L190E:      lda (L0076,X)          ; Get sprite databyte
L1910:      sta L0084

            lda #$08
            sta L0083

            lda L007F              ; Get color
            ldx L0081
            beq L1920              ; No shift needed

L191C:      lsr A                  ; Shift color x pixels
            lsr A

            dex
            bne L191C

L1920:      sta L0082              ; Save shifted byte

            lda #$04               ; Max shift = 4
            sec
            sbc L0081              ; Calc shift 2nd byte
            sta L0081

            ldx #$00
L192B:
            asl L0084              ; Shift out pixel sprite
            bcc L1935              ; If clear, skip plotting
            lda (L0070),Y          ; Get screen byte
L1932:
            ora L0082              ; OR/XOR with sprite byte
            sta (L0070),Y          ; Put screen byte

L1935:      dec L0083              ; Check for address boundery
            bne L194B

            inc L0076              ; Next sprite databyte
            bne L193F
            inc L0077

L193F:      dec L0087              ; C6 87
            beq L1961              ; F0 1E
            lda (L0076,X)          ; Get sprite databyte
L1945:      sta L0084              ; 85 84

            lda #$08               ; A9 08
            sta L0083              ; 85 83

L194B:      lsr L0082              ; Shift pixel
            lsr L0082

            dec L0081              ; C6 81
            bne L192B              ; D0 DA

            iny                    ; Point to byte right 

            lda L007F              ; Get color
            sta L0082

            lda #$04               ; Reset x-shift counter
            sta L0081
            jmp L192B              ; Loop

L1961:      dec L0078              ; Check if heigth is reached
            beq L196B
            jsr L196C
            jmp L1902

L196B:      rts                    ; 60

;------------------------------------------------
; Calculate address $70/$71 next line
;------------------------------------------------

L196C:
            clc                    ; No add $20 to $70/$71
            lda L0070
            adc #$20
            sta L0070
            lda L0071
            adc #0
            sta L0071
            rts

;------------------------------------------------
; Calculate screen address from X,Y
; - $70/$71 = Screenaddress 
; - $72 = y-shift in characterblock (0-7)
; - $73 = x-shift (0-3)
; - $74 = tmp x
; - $75 = tmp y
;------------------------------------------------

L1987:      stx L0074              ; Save x
            sty L0075              ; Save y

            lda #$00               ; Reset hb
            sta L0071

            tya                    ; Invert Y 
            eor #$FF
            tay
            sec
            sbc #64

            sta L0070
            asl L0070
            rol L0071
            asl L0070
            rol L0071
            asl L0070
            rol L0071
            asl L0070
            rol L0071
            asl L0070
            rol L0071

            txa                    ; Set X-shift (0-3)
            and #$03
            sta L0073

            txa                    ; Set lb=x/4
            lsr A
            lsr A
            clc
            adc L0070
            sta L0070
            lda #$80
            adc L0071
            sta L0071
            rts

;------------------------------------------------
; Calculate sprite address from A int $76/$77
; $76 = lb sprite addr
; $77 = hb sprite addr
; $78 = Height sprite databyte (pixels)
; $79 = Width sprite databyte (pixels)
; $7A = Width sprite databyte (bytes)
;------------------------------------------------

L19D7:      ldy #$00               ; Spriteaddress = sprites + 4 * A
            sty L0077
            asl A
            rol L0077
            asl A
            rol L0077
            adc #<sprites
            sta L0076
            lda L0077
            adc #>sprites
            sta L0077

            lda (L0076),Y          ; Get width in pixels
            sta L0079              ; Store

            clc                    ; Calc width in bytes = (pixels+7)/8
            adc #$07
            lsr A
            lsr A
            lsr A
            sta L007A              ; Store

            iny
            lda (L0076),Y          ; Get height in pixels
            sta L0078              ; Store

            iny
            lda (L0076),Y          ; Get lb spriteaddress
            tax
            iny
            lda (L0076),Y          ; Get hb spriteaddress
            stx L0076              ; Store lb
            sta L0077              ; Store hb
            rts

;------------------------------------------------
; Plot sprite A at X,Y (bytes)
;------------------------------------------------

L1A08:      pha                    ; Save spritenr

            txa                    ; x=x*8
            asl A
            asl A
            asl A
            tax

            tya                    ; y=y*8
            asl A
            asl A
            asl A
            tay

            jsr L1987              ; Calc screen address
            pla                    ; Get spritenr
            jsr L19D7              ; Calc sprite address
            jsr L1902              ; Plot sprite
            rts

;------------------------------------------------
; Print string
; X = lb stringaddress
; Y = hb stringaddress
; stringaddress: len,string
;------------------------------------------------

L1A22:
	stx L0070              ; Set lb stringpointer
	sty L0071              ; Set hb stringpointer
	jsr PUTSTRING
	rts

;------------------------------------------------
; Wait for keypress 
;------------------------------------------------

L1A37:
	lda #$28     ; Key 'H'
        jsr scankey
	bcc L1A6A    ; No

L1A44:
	lda #$28     ; Key 'H'
        jsr scankey
	bcc L1A63    ; No

	lda #$3b     ; Key ESC
        jsr scankey
	bcc L1A63    ; No

	lda #$80     ; No key pressed
	sta L0060
	rts
L1A63:
	jsr L1A6A    ; Scan l,r,u,d,jump  keys
	lda L0060
	beq L1A44
L1A6A:
	lda #$00     ; Mark no key read
	sta L0060  

	lda L001B    ; Check if joystick available
	beq no_joy   ; If not scan keys
	jsr joyget   ; Otherwise scan joystick
	sta L0060
	jmp L1A80

no_joy:
	lda #$01
	sta L0080

	lda L0061    ; Scan key right
	jsr L1A8C
	lda L0062    ; Scan key left
	jsr L1A8C
	lda L0063    ; Scan key down
	jsr L1A8C
	lda L0064    ; Scan key up
 	jsr L1A8C
	lda L0065    ; Scan key jump
 	jsr L1A8C
L1A80:
	rts
L1A8C:
	jsr scankey
	bcc L1A9D    ; No

	lda L0060    ; Mark key read
	ora L0080
	sta L0060
L1A9D:
	asl L0080
	rts

;------------------------------------------------
; Calculate random nr in $66
;------------------------------------------------

L1AA0:      lda L0066
            and #$48
            adc #$38
            asl A
            asl A
            rol L0069
            rol L0068
            rol L0067
            rol L0066
            rts

;------------------------------------------------
; Update score in A to score byte X
;------------------------------------------------

L1AB1:      ldy #red               ; Color magenta
            sty L007F

            ldy L0028,X            ; Get score digit

            clc                    ; Add A to scoredigit
            adc L0028,X
            cpx #$03
            bne L1AC0

            inc L003E              ; E6 3E
L1AC0:      cmp #$0A               ; Scoredigit >10?
            bcc L1AD2              ; No

            sec                    ; Yes
            sbc #$0A
            sta L0028,X            ; Store Scoredigit MOD 10
            jsr L1AD4              ; Print digit

            lda #$01
            dex                    ; Repeat until x=0
            bpl L1AB1
            rts

L1AD2:      sta L0028,X            ; Store Scoredigit

L1AD4:      cpx #$02               ; X>2
            bcs L1AD9              ; No
            rts                    ; Yes

L1AD9:      sta L008C              ; Save new scoredigit
            stx L008D              ; Save digit nr
            sty L008E              ; Save old scoredigit

            lda L003F              ; Get startposition scoredigit
            clc                    ; Add 4 for every position
L1AE2:      adc #$04
            dex
            bpl L1AE2

            sta L008B              ; Save position digit
            tax                    ; Set x-pos
            lda L008E              ; Get old scoredigit
            ldy #190               ; Set y-pos=190
            jsr L1AFD              ; Erase number

            lda L008C              ; Get new scoredigit
            ldx L008B              ; Set x-pos
            ldy #190               ; Set y-pos=190
            jsr L1AFD              ; Print number
            ldx L008D              ; Get digit nr
            rts

;------------------------------------------------
; Print number in A at position X,Y
;------------------------------------------------

L1AFD:      pha                    ; Save spritenr
            jsr L1987              ; Calc screen address
            pla                    ; Get spritenr
            clc
            adc #$1F               ; Point to number sprite
            jsr L19D7              ; Calc sprite address
            jsr L1B82              ; Plot sprite
            rts

;------------------------------------------------
; Copy screen $8000-$9800 into buffer $6000-$7800
;------------------------------------------------

L1B0C:
            ldy #$00
            sty L0070
            sty L007B
            lda #$80
            sta L0071
            lda #$60
            sta L007C
L1B1A:      lda (L0070),Y          ; Read $8000-$9800
            sta (L007B),Y          ; Save $6000-$7800
            iny
            bne L1B1A
            inc L007C
            inc L0071
            lda L0071
            cmp #$98
            bne L1B1A
            rts

;------------------------------------------------
; Erase sprite by copying background to screen
;------------------------------------------------

L1B2C:      jsr L1B56              ; Point background buffer

            ldy L007A
	iny
	iny
L1B37:      lda (L007B),Y          ; Load background
            sta (L0070),Y          ; Plot over screen
            dey
            bpl L1B37

L1B4B:      dec L0078
            beq L1B55
            jsr L196C              ; Calculate address next line
            jmp L1B2C
L1B55:      rts

;------------------------------------------------
; Point to background buffer $7B/$7C
;------------------------------------------------

L1B56:      lda L0070              ; Get screen address
            sta L007B
            lda L0071
            sec
            sbc #$20               ; Background = Screen - $2000
            sta L007C
            rts

;------------------------------------------------
; Plot egg or seed
;------------------------------------------------

L1B62:
            txa                    ; x=x*8
            asl A
            asl A
            asl A
            tax

            tya                    ; y=y*8
            asl A
            asl A
            asl A
            tay
            jsr L1987              ; Calc screen address

            jsr L1B56              ; Calc dest address
            ldx #$02
            ldy #0
L1B7A:
            lda #$00
            sta (L0070),Y
            sta (L007B),Y
            tya
            clc
            adc #$20
            tay
            bne L1B7A
            inc L0070
            inc L007B
            dex
            bne L1B7A
            rts

;------------------------------------------------
; Invert sprite
;------------------------------------------------

L1B82:
            lda #$45               ; Change OR in EOR
            sta L1932              ; in plot routine
            jsr L1902              ; Invert sprite
            lda #$05               ; Change EOR in OR
            sta L1932              ; in plot routine
            rts

;------------------------------------------------
; Read/write interval timer increments 100 times/sec
; Set framerate on 30000 usec
;------------------------------------------------

L1B90:
	lda $b809
	bpl L1B90
	lda #<30000
	sta $b808
	lda #>30000
	sta $b809

	rts

;------------------------------------------------
; Draw level
;------------------------------------------------

L1BB3:
	jsr clear4

            jsr L1D3E              ; Draw score board

            lda L005C              ; Get address leveldata from pointertable at $0cc0
            asl A
            tay
            lda L34C0,Y
            sta L0051
            iny
            lda L34C0,Y
            sta L0052

            ldy #$00
            lda (L0051),Y          ; Read nr of walls to plot (3 bytes per plot)
            sta L0053              ; Save at $53
            iny
            lda (L0051),Y          ; Read nr of ladders to plot (3 bytes per plot)
            sta L0054              ; Save at $54
            iny
            lda (L0051),Y          ; Read elevator flag
            sta L0055              ; Save at $55
            iny
            lda (L0051),Y          ; Read nr of seed to plot (2 bytes per plot)
            sta L0056              ; Save at $56
            iny
            lda (L0051),Y          ; Read nr of birds
            sta L0057              ; Save at $57

            lda #$00               ; Fill $600-$7FF with 0
            tax
L1BE7:      sta L0600,X
            sta L0700,X
            dex
            bne L1BE7

; Plot walls  ---------------------------------------------------
            lda #blue               ; Color green
            sta L007F

            lda L0053              ; Nr of wall sprites
            sta L008A

            sty L0089              ; Save leveldata pointer

L1BFA:      ldy L0089              ; Get leveldata pointer
            iny
            lda (L0051),Y
            sta L008B              ; Sprite Y
            iny
            lda (L0051),Y
            sta L008C              ; Sprite X-start
            iny
            lda (L0051),Y          ; Sprite X-end
            sec
            sbc L008C
            sta L008D              ; Nr of sprites
            sty L0089              ; Save leveldata pointer

L1C10:      lda #$01               ; Wall sprite
            ldy L008B
            ldx L008C
            jsr L249F              ; Copy into background buffer

            ldx L008C              ; Get x-pos 
            jsr L1A08              ; Plot sprite
            inc L008C              ; Next x-pos screen
            dec L008D              ; Decrement col-counter
            bpl L1C10              ; Repeat if not last column
            dec L008A              ; Decrement row-counter
            bne L1BFA              ; Repeat if not last row

; Plot ladders ----------------------------------------------------
            lda #red               ; Color magenta
            sta L007F

            lda L0054              ; Nr of ladders
            sta L008A

L1C30:      ldy L0089              ; Get leveldata pointer
            iny
            lda (L0051),Y
            sta L008B              ; Sprite Y
            iny
            lda (L0051),Y
            sta L008C              ; Sprite X-start
            iny
            lda (L0051),Y          ; Sprite X-end
            sec
            sbc L008C
            sta L008D              ; Nr of sprites
            sty L0089

L1C46:      ldx L008B              ; Get x-pos
            ldy L008C              ; Get y-pos
            jsr L2487              ; Get background nr
            beq L1C56              ; F0 07
            ldx L008B              ; A6 8B
            jsr L1B62              ; 20 62 1B

            lda #$01
L1C56:      ora #$02               ; Set ladder
            ldx L008B
            ldy L008C
            jsr L249F              ; Copy into background buffer

            lda #$02               ; Ladder sprite
            ldx L008B
            ldy L008C
            jsr L1A08              ; Plot sprite
            inc L008C              ; Point to 1 position up
            dec L008D              ; Decrement sprite counter
            bpl L1C46
            dec L008A              ; Next ladder
            bne L1C30

; Plot elevators ------------------------------------------------
            lda L0055              ; Get elevator flag
            beq L1C82              ; No elevator, skip
            ldy L0089              ; Get x-pos
            iny
            lda (L0051),Y
            sty L0089              ; Save x-pos (bytes)
            asl A
            asl A
            asl A
            sta L0058              ; Save x-pos (pixels)

; Plot eggs -----------------------------------------------------
L1C82:      lda #yellow               ; Color yellow
            sta L007F

            lda #$00
            sta L008A              ; Reset egg counter
            sta L0039              ; 85 39
            lda L004E              ; Get leveldatapointer
            sta L0088              ; Save leveldatapointer
L1C90:      ldy L0089
            iny
            lda (L0051),Y          ; Get x-pos
            sta L008B
            iny
            lda (L0051),Y          ; Get y-pos
            sta L008C
            sty L0089              ; Save leveldatapointer

            ldx L0088              ; Load buffer pointer
            lda L0510,X            ; Load background
            bne L1CBF 

            lda L008A              ; Marker=Egg counter *16
            asl A
            asl A
            asl A
            asl A
            adc #$04               ; First egg $04,$14,$24..
            ldx L008B
            ldy L008C
            jsr L249F              ; Copy into background buffer

            lda #$03               ; Egg sprite
            ldx L008B
            ldy L008C
            jsr L1A08              ; Plot sprite
            inc L0039

L1CBF:      inc L0088
            inc L008A              ; Inc egg counter
            lda L008A              ; Get egg counter
            cmp #$0C               ; Last egg nr 12?
            bcc L1C90

; Plot seed -----------------------------------------------------
            lda #red               ; Color magenta
            sta L007F

            lda #$00
            sta L008A
            lda L004E
            sta L0088
L1CD5:      ldy L0089
            iny
            lda (L0051),Y          ; Read x-pos
            sta L008B
            iny
            lda (L0051),Y          ; Read y-pos
            sta L008C
            sty L0089
            ldx L0088

            lda L0520,X
            bne L1D02

            lda L008A              ; Number seed as $08,$18,$28 ....
            asl A
            asl A
            asl A
            asl A
            adc #$08
            ldx L008B
            ldy L008C
            jsr L249F              ; Copy into background buffer

            lda #$04               ; Seed sprite
            ldx L008B
            ldy L008C
            jsr L1A08              ; Plot sprite

L1D02:      inc L0088
            inc L008A
            lda L008A
            cmp L0056
            bcc L1CD5

; Plot duck cage ------------------------------------------------
            lda #yellow            ; Plot duck cage in yellow
            sta L007F

            ldx #$00               ; X=0
            ldy #169               ; Y=220
            jsr L1987
            ldx #$13               ; Duck cage with duck
            lda L0035              ; Check for cage with or without duck
            beq L1D1E
            inx                    ; Duck cage without duck
L1D1E:      txa
            jsr L19D7
            jsr L1902              ; Plot cage

; Copy bird data into buffer------------------------------------
            ldy L0089              ; Get leveldatapointer
            ldx #$00
L1D29:      iny                    ; Copy birddata into buffer
            lda (L0051),Y          ; Get x-pos
            sta L040A,X            ; Store x-pos
            iny
            lda (L0051),Y          ; Get y-pos
            sta L040F,X            ; Store y-pos
            inx
            cpx #$05
            bcc L1D29

            jsr L1B0C              ; Copy screen into buffer
            rts                    ; 60

;------------------------------------------------
; Draw score board
;------------------------------------------------

; SCORE ------------------------------------------------

L1D3E:      lda #red               ; Color magenta
            sta L007F

            ldx #$00               ; Print 'SCORE' at 0,191
            ldy #191
            jsr L1987              ; Calc screen address
            lda #$29               ; Sprite $29
            jsr L19D7              ; Calc sprite address
            jsr L1902              ; Plot sprite

            ldx L005D              ; Calculate pos score
            lda #$00
            clc
L1D56:      adc #26
            dex
            bpl L1D56
            sec
            sbc #2
            tax                    ; x=player*26-2
            ldy #191
            jsr L1987
            lda #$2A               ; Invert playerscore at x,191
            jsr L19D7
            jsr L1902

            ldx #$00               ; Print all player scores
            stx L0088
L1D70:      jsr L1E6A
            inc L0088
            ldx L0088
            cpx L005E              ; Max players
            bcc L1D70

; PLAYER ------------------------------------------------

            lda #red               ; Color magenta
            sta L007F

            ldx #$00               ; Print 'Player' at 0,179
            ldy #179
            jsr L1987
            lda #$2B
            jsr L19D7
            jsr L1902

            ldx #25               ; Print current playernr at 27,178
            ldy #178
            jsr L1987
            lda L005D
            clc
            adc #$20
            jsr L19D7
            jsr L1B82

; LEVEL ------------------------------------------------

            ldx #30               ; Print 'Level' at 34,179
            ldy #179
            jsr L1987
            lda #$2C
            jsr L19D7
            jsr L1902

            lda #$00               ; Print levelnr xxx at 59,178
            sta L008B
            sta L008C

            ldx L0050              ; Get levelnr
            inx
            stx L008D
            lda L008D

            ldx #$00
L1DBE:      cmp #$0A
            bcc L1DC9
            sec
            sbc #$0A
            inx
            jmp L1DBE

L1DC9:      sta L008D              ; Save digit1
            txa
            ldx #$00
L1DCE:      cmp #$0A
            bcc L1DD9
            sec
            sbc #$0A
            inx
            jmp L1DCE

L1DD9:      sta L008C              ; Save digit2
            stx L008B              ; Save digit3
 
            lda L008B              ; Print digit3 at 55,178
            beq L1DE8              ; Skip if 0
            ldx #47
            ldy #178
            jsr L1AFD

L1DE8:      lda L008C              ; Print digit2 at 59,178
            ldx #51
            ldy #178
            jsr L1AFD

            lda L008D              ; Print digit1 at 63,178
            ldx #55
            ldy #178
            jsr L1AFD

; BONUS ------------------------------------------------

            ldx #60               ; Print 'Bonus' at 78,179
            ldy #179
            jsr L1987
            lda #$2D
            jsr L19D7
            jsr L1902

L1E09:      lda L003A              ; Print digit1 at 102,178
            ldx #82
            ldy #178
            jsr L1AFD

            lda L003B              ; Print digit2 at 107,178
            ldx #86
            ldy #178
            jsr L1AFD

            lda L003C              ; Print digit3 at 112,178
            ldx #90
            ldy #178
            jsr L1AFD

            lda #$00               ; Print 0 at 117,178
            ldx #94
            ldy #178
            jsr L1AFD

; TIME ------------------------------------------------

L1E2D:      ldx #99               ; Print 'Time' at 126,179
            ldy #179
            jsr L1987
            lda #$2E
            jsr L19D7
            jsr L1902

            lda L004D              ; Time depending of levelnr
            lsr A
            cmp #$08
            bcc L1E45
            lda #$08
L1E45:      eor #$FF
            sec
            adc #$09
            sta L001D              ; Print Digit1 at 145,178
            ldx #116
            ldy #178
            jsr L1AFD

            lda #$00
            sta L001E              ; Print digit2 at 150,178
            ldx #120
            ldy #178
            jsr L1AFD

            lda #$00
            sta L001F              ; Print digit3 at 155,178
            ldx #124
            ldy #178
            jsr L1AFD

            rts

;------------------------------------------------
; Print score + lives sprites
;------------------------------------------------

L1E6A:      lda #$00               ; Calc player*$26
            clc
L1E6D:      adc #26
            dex
            bpl L1E6D
            sec
            sbc #$02
            sta L008B              ; Save player*$26-2

            lda #red               ; Color magenta
            sta L007F

            lda L0088              ; Get playernr
            asl A
            asl A
            asl A
            asl A
            asl A
            asl A
            tax                    ; Calc offest
            inx                    ; Inc offset
            inx                    ; Inc offset
            stx L008D              ; Save offset

            ldx L008B
            inx
            stx L008C              ; x-pos

            lda #$06               ; Nr of digits
            sta L008E

L1E91:      ldx L008D
            lda L0500,X            ; Get digit

            ldx L008C              ; Get x-pos
            ldy #190               ; Set y-pos
            jsr L1AFD              ; Print digit

            lda L008C              ; xpos + 5
            clc
            adc #$04
            sta L008C

            inc L008D              ; Inc offset

            dec L008E              ; Next digit
            bne L1E91

            lda #yellow            ; Color yellow
            sta L007F

            ldx L0088              ; Get playernr
            lda L0020,X            ; Get lives
            beq L1EDD              ; Skip if 0
            cmp #$06
            bcc L1EBA              ; Limit to 6
            lda #$06
L1EBA:      sta L008E

            lda L008B              ; Get sprite pos
            sta L008C

L1EC0:      ldx L008C              ; Get x-pos
            ldy #182               ; Get y-pos
            jsr L1987              ; Calc screen addr
            lda #$2F               ; Lives sprite
            jsr L19D7              ; Calc sprite addr
            jsr L1902              ; Plot sprite
            dec L008E              ; Next life
            beq L1EDD              ; if last, end
            lda L008C              ; xpos + 4
            clc
            adc #$04
            sta L008C
            jmp L1EC0
L1EDD:      rts

;------------------------------------------------
; Update man
;------------------------------------------------

L1EDE:      lda #$00
            sta L0046              ; Reset x-dir
            sta L0047              ; Reset y-dir

            lda L0060              ; Read key read flag
            lsr A
            bcc L1EEB
            inc L0046              ; Key right pressed

L1EEB:      lsr A
            bcc L1EF0
            dec L0046              ; Key left pressed

L1EF0:      lsr A
            bcc L1EF5
            dec L0047              ; Key down pressed

L1EF5:      lsr A
            bcc L1EFA
            inc L0047              ; Key up pressed
L1EFA:
            asl L0047              ; Y-dir x 2

            lda L0049              ; Get movement man
            beq L1F16              ; Horizontal

            cmp #$02               ; Jump?
            bne L1F07              ; No
            jmp L1FFC              ; Yes

L1F07:      bcs L1F0C              ; Jumpstep=1?
            jmp L1F9D              ; Yes

L1F0C:      cmp #$03               ; Fall?
            bne L1F13              ; No
            jmp L215E              ; Yes

L1F13:
            jmp L21B9              ; Scan key jumped

L1F16:
            lda L0060
            and #$10
            beq L1F1F
            jmp L214B              ; Key jump pressed

; Handle ladder climbing -----------------------------
L1F1F:      lda L0047              ; Get y-dir
            beq L1F53              ; Horizontal move

            ldx L0044              ; Check for ladder
            cpx #$03
            bne L1F53              ; No

            lda L0047              ; Get y-dir
            bmi L1F3C              ; Going down

            ldx L0042              ; Check floor above man
            ldy L0043
            iny
            iny
            jsr L2487              ; Get background nr
            and #$02               ; Check for ladder
            beq L1F53              ; No ladder
            bne L1F48              ; Ladder

L1F3C:      ldx L0042              ; Check floor under man
            ldy L0043
            dey
            jsr L2487              ; Get background nr
            and #$02               ; Check for ladder
            beq L1F53              ; No ladder

L1F48:      lda #$00               ; X-dir man=0
            sta L0046
            lda #$01
            sta L0049              ; Man climbing ladder
            jmp L1F94

; Handle horizontal move -----------------
L1F53:      lda #$00               ; Y-dir man=0
            sta L0047

            lda L0044              ; Get x-pos man mod 8
            clc
            adc L0046              ; Add x-dir

            ldx L0042              ; Get x-pos man in bytes
            cmp #$00               ; Check left border byte
            bpl L1F63              ; Next move in same tile
            dex                    ; Point to tile left from man
L1F63:      cmp #$08               ; Check right border byte
            bmi L1F68              ; Next move in same tile
            inx                    ; Point to tile right from man

L1F68:      ldy L0043              ; Get y-pos man in bytes
            dey                    ; Point tile below man
            jsr L2487              ; Get background nr
            and #$01               ; Check wall
L1F70:      bne L1F8B              ; Wall

            tay                    ; Y=0
            ldx #$FF               ; 
            lda L0046              ; Get x-dir
            clc
            adc L0044              ; Add x-pos man mod 8
            and #$07
            cmp #$04               ; Check 
            bcs L1F83              ; B0 03
            ldx #$01               ; A2 01
            iny                    ; C8

L1F83:      stx L004B              ; 86 4B
            sty L004A              ; 84 4A
            lda #$03
            sta L0049              ; Man falling
L1F8B:
            jsr L2303              ; Check for tile under man for falling
            bcc L1F94              ; No tile, move horizontal while falling
            lda #$00               ; Stop moving horizontal
            sta L0046

L1F94:      lda L0046              ; Get x-dir man
            beq L1F9A              ; Skip if no movement
            sta L004C              ; If moving, save current dir
L1F9A:
            jmp L21F6              ; Erase man

; Check jump key ----------------------------------
L1F9D:      lda L0060
            and #$10
            beq L1FA6              ; Key jump not pressed
            jmp L214B              ; Key jump pressed

L1FA6:      lda L0046              ; Get man x-dir
            beq L1FC5              ; Man not moving horizontal

            ldx L0045              ; Get y-pos man mod 8
            bne L1FC5              ; D0 17

            ldx L0042              ; Get x-pos man in bytes
            ldy L0043              ; Get y-pos man in bytes
            dey                    ; Point to tile below
            jsr L2487              ; Get background nr
            and #$01               ; Check if wall or end of ladder
            beq L1FC5              ; No wall or end of ladder

            lda #$00               ; Stop moving vertical
            sta L0047
            lda #$00               ; Stop moving horizontal
            sta L0049
            jmp L1FF5

L1FC5:      lda #$00
            sta L0046              ; Man x-dir = 0
            lda L0047              ; Get man y-dir
            beq L1FF5              ; F0 28

            lda L0045              ; A5 45
            bne L1FF5              ; D0 24
            lda L0047              ; A5 47
            bmi L1FE7              ; 30 12
            ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            iny                    ; C8
            iny                    ; C8
            jsr L2487              ; Get background nr
            and #$02               ; 29 02
            bne L1FF5              ; D0 13
            sta L0047              ; 85 47
            jmp L1FF5              ; 4C F5 1F
L1FE7:      ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            dey                    ; 88
            jsr L2487              ; Get background nr
            and #$02               ; 29 02
            bne L1FF5              ; D0 02
            sta L0047              ; 85 47

L1FF5:      lda #$00               ; A9 00
            sta L004C              ; 85 4C
            jmp L21F6              ; 4C F6 21

; Jumping routine ----------------------------------------
L1FFC:      lda L004B              ; A5 4B
            sta L0046              ; 85 46
            lda L0047              ; A5 47
            sta L0089              ; 85 89
L2004:      lda L004A              ; Get jump/fall distance
            lsr A
            lsr A                  ; Divide by 4
            cmp #$06               ; Check if 6
            bcc L200E              ; Less then 6
            lda #$06               ; More then 6, limit to 6
L200E:      eor #$FF               ; Invert
            sec                    ; 38
            adc #$02               ; 69 02
            sta L0047              ; 85 47
            inc L004A              ; E6 4A
            lda L0041              ; A5 41
            cmp #169               ; C9 DC
            bcc L2028              ; 90 0B
            lda #$FF               ; A9 FF
            sta L0047              ; 85 47
            lda #$0C               ; A9 0C
            sta L004A              ; 85 4A
            jmp L20DD              ; 4C DD 20

L2028:      lda L0044              ; A5 44
            clc                    ; 18
            adc L0046              ; 65 46
            cmp #$03               ; C9 03
            bne L2091              ; D0 60
            lda L0089              ; A5 89
            beq L2091              ; F0 5C
            bmi L2068              ; 30 31

; Up must be pressed - jumping see if land on ladder ---------
            ldx L0042              ; Get x-pos man
            ldy L0043              ; Get y-pos above man
            iny
            jsr L2487              ; Get background nr
            and #$02               ; Ladder?
            bne L2056              ; Branch if a ladder, or platform ladder overlap (ok land on ladder) ---------
L2043:      ldx L0042              ; Get x-pos man
L2045:      ldy L0043              ; Get y-pos above man
            iny
            lda L0045              ; Check if man in upper half tile
            cmp #$04
            bcc L204F              ; Man in lower half tile
            iny                    ; Man in upper half tile
L204F:      jsr L2487              ; Get background nr
            and #$02               ; Ladder?
            beq L2091              ; Branch if not a ladder, or platform ladder overlap (don't land on ladder)

	lda L004A                  ; Solution to avoid jumping trough platforms on ladder
	cmp #$09
	bcs L2091
 
; Ok, land on ladder (going up) -----------------------------
L2056:
            lda #$01
            sta L0049              ; Man climbing ladder
            lda L0045              ; A5 45
            clc                    ; 18
            adc L0047              ; 65 47
            and #$01               ; 29 01
            beq L2065              ; F0 02
            inc L0047              ; E6 47
L2065:      jmp L2148              ; 4C 48 21

; Down must be pressed - jumping see if land on ladder ---------
L2068:      ldx L0042              ; Get x-pos man
            ldy L0043              ; Get y-pos man
            jsr L2487              ; Get background nr
            and #$02               ; Ladder?
            beq L2091              ; Branch if not a ladder, or platform ladder overlap (can't land here then)
            ldx L0042              ; Get x-pos man
            ldy L0043              ; Get y-pos above man
            iny
            jsr L2487              ; Get background nr
            and #$02               ; Ladder?
            beq L2091              ; Branch if not a ladder, or platform ladder overlap (can't land here then)

; Ok, land on ladder (going down)
            lda #$01
            sta L0049              ; Man climbing ladder
            lda L0045              ; A5 45
            clc                    ; 18
            adc L0047              ; 65 47
            and #$01               ; 29 01
            beq L208E              ; F0 02
            dec L0047              ; C6 47
L208E:      jmp L2148              ; 4C 48 21

L2091:      lda L0047              ; A5 47
            clc                    ; 18
            adc L0045              ; 65 45
            beq L20B4              ; F0 1C
            bpl L20C7              ; 10 2D
            ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            dey                    ; 88
            jsr L2487              ; Get background nr
            and #$01               ; 29 01
            beq L20DD              ; F0 37
            lda #$00
            sta L0049              ; Man moving horizontal
            lda #$00               ; A9 00
            sec                    ; 38
            sbc L0045              ; E5 45
            sta L0047              ; 85 47
            jmp L20DD              ; 4C DD 20

L20B4:      ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            dey                    ; 88
            jsr L2487              ; Get background nr
            and #$01               ; 29 01
            beq L20DD              ; F0 1D
            lda #$00
            sta L0049              ; Man moving horizontal
            jmp L20DD              ; 4C DD 20

L20C7:      cmp #$08               ; C9 08
            bne L20DD              ; D0 12
            ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            jsr L2487              ; Get background nr
            and #$01               ; 29 01
            beq L20DD              ; F0 07
            lda #$00
            sta L0049              ; Man moving horizontal
            jmp L20DD              ; 4C DD 20

L20DD:      lda L0055              ; A5 55
            beq L213A              ; F0 59
            lda L0058              ; A5 58
            sec                    ; 38
            sbc #$01               ; E9 01
            cmp L0040              ; C5 40
            bcs L213A              ; B0 50
            adc #$0A               ; 69 0A
            cmp L0040              ; C5 40
            bcc L213A              ; 90 4A
            lda L0041              ; A5 41
            sec                    ; 38
            sbc #$11               ; E9 11
            sta L008B              ; 85 8B
            sbc #$02               ; E9 02
            clc                    ; 18
            adc L0047              ; 65 47
            sta L008C              ; 85 8C
            lda L0059              ; A5 59
            cmp L008B              ; C5 8B
            beq L210A              ; F0 06
            bcs L2114              ; B0 0E
            cmp L008C              ; C5 8C
            bcc L2114              ; 90 0A
L210A:      ldx L005B              ; A6 5B
            bne L2111              ; D0 03
            clc                    ; 18
            adc #$01               ; 69 01
L2111:      jmp L2127              ; 4C 27 21

L2114:      lda L005A              ; Get y-pos elevator high
            cmp L008B              ; C5 8B
            beq L2120              ; F0 06
            bcs L213A              ; B0 1E
            cmp L008C              ; C5 8C
            bcc L213A              ; 90 1A

L2120:      ldx L005B              ; Get elevator flag
            beq L2127              ; Flag was elevator low 
            clc                    ; Flag was elevator high
            adc #$01               ; 69 01
L2127:      sec                    ; 38
            sbc L008B              ; E5 8B
            clc                    ; 18
            adc #$01               ; 69 01
            sta L0047              ; 85 47

            lda #$00               ; Set tone
            sta L004A

            lda #$04
            sta L0049              ; Man on elevator
            jmp L2148

L213A:      jsr L2303              ; Check for wall under man for falling
            bcc L2148              ; No wall

            lda #$00               ; Invert x-dir
            sec
            sbc L0046
            sta L0046
            sta L004B              ; Save x-dir
L2148:      jmp L21F6

;------------------------------------------------
; Key jump pressed
;------------------------------------------------

L214B:      lda #$00               ; A9 00
            sta L004A              ; 85 4A

            lda #$02
            sta L0049              ; Man jump
            lda L0046              ; Get x-direction
            sta L004B              ; Set jump direction
            beq L215B              ; Branch if just jump straight up
            sta L004C              ; New x-movement (-1=left,0=up/down,1=right)
L215B:      jmp L1FFC

L215E:      inc L004A              ; E6 4A
            lda L004A              ; A5 4A
            cmp #$04               ; C9 04
            bcs L2171              ; B0 0B
            lda L004B              ; A5 4B
            sta L0046              ; 85 46
            lda #$FF               ; A9 FF
            sta L0047              ; 85 47
            jmp L2183              ; 4C 83 21
L2171:      lda #$00               ; A9 00
            sta L0046              ; 85 46
            lda L004A              ; A5 4A
            lsr A                  ; 4A
            lsr A                  ; 4A
            cmp #$04               ; C9 04
            bcc L217F              ; 90 02
            lda #$03               ; A9 03
L217F:      eor #$FF               ; 49 FF
            sta L0047              ; 85 47
L2183:      lda L0047              ; A5 47
            clc                    ; 18
            adc L0045              ; 65 45
            beq L21A6              ; F0 1C
            bpl L21B6              ; 10 2A
            ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            dey                    ; 88
            jsr L2487              ; Get background nr
            and #$01               ; 29 01
            beq L21B6              ; F0 1E
            lda #$00
            sta L0049              ; Man moving horizontal
            lda #$00               ; A9 00
            sec                    ; 38
            sbc L0045              ; E5 45
            sta L0047              ; 85 47
            jmp L21B6              ; 4C B6 21
L21A6:      ldx L0042              ; A6 42
            ldy L0043              ; A4 43
            dey                    ; 88
            jsr L2487              ; Get background nr
            and #$01               ; 29 01
            beq L21B6              ; F0 04
            lda #$00
            sta L0049              ; Man moving horizontal
L21B6:      jmp L21F6              ; 4C F6 21

L21B9:      lda L0060              ; Key jump pressed
            and #$10
            beq L21C2              ; Yes
            jmp L214B              ; No

L21C2:      lda L0058              ; A5 58
            sec                    ; 38
            sbc #$01               ; E9 01
            cmp L0040              ; C5 40
            bcs L21D1              ; B0 06
            adc #$0A               ; 69 0A
            cmp L0040              ; C5 40
            bcs L21DB              ; B0 0A
L21D1:      lda #$00               ; A9 00
            sta L004A              ; 85 4A
            sta L004B              ; 85 4B
            lda #$03
            sta L0049              ; Man falling
L21DB:      lda #$01               ; A9 01
            sta L0047              ; 85 47
            lda L0046              ; A5 46
            beq L21E5              ; F0 02
            sta L004C              ; 85 4C
L21E5:      jsr L2303              ; 20 03 23
            bcc L21EE              ; 90 04
            lda #$00               ; A9 00
            sta L0046              ; 85 46
L21EE:      lda L0041              ; A5 41
            cmp #169               ; C9 DC
            bcc L21F6              ; 90 02
            inc L004F              ; E6 4F

L21F6:      lda L0048              ; Get current sprite nr man
            jsr L19D7
            ldx L0040              ; Get x-pos man
            ldy L0041              ; Get y-pos man
            jsr L1987
            jsr L1B2C              ; Erase man

            lda L0040              ; Update x-pos man
            clc
            adc L0046              ; Step size/direction
            sta L0040

            lda L0044              ; Get x-pos man mod 8
            clc
            adc L0046              ; Add x-dir
            bpl L2215              ; Check left border byte
            dec L0042              ; Byte cross to the left
L2215:      cmp #$08               ; Check right border byte
            bmi L221B              ; No byte cross
            inc L0042              ; Byte cross to the right
L221B:      and #$07               ; Mask byte
            sta L0044              ; Save x-pos man mod 8

            lda L0041              ; Update y-pos man
            clc
            adc L0047              ; Step size/direction
            sta L0041

            lda L0045              ; Get y-pos man mod 8
            clc
            adc L0047              ; Add y-dir
            bpl L222F              ; Check low border byte
            dec L0043              ; Byte cross down
L222F:      cmp #$08               ; Check upper border byte
            bmi L2235              ; No byte cross
            inc L0043              ; Byte cross up
L2235:      and #$07               ; Mask byte
            sta L0045              ; Save y-pos man mod 8

            ldx #$06               ; Get sprite man stand right
            lda L004C              ; Get current x-dir man
            beq L224B              ; Man on ladder
            bpl L2243              ; Man moving right

            ldx #$09               ; Get sprite man stand left
L2243:      stx L0088              ; Save

            lda L0044              ; Get x-pos man mod 8
            lsr A                  ; Shift 2 pixels to the right
            jmp L2252              ; 4C 52 22

L224B:      lda #$0C               ; Get sprite man climbing
            sta L0088              ; Save

            lda L0045              ; Get y-pos man mod 8
            lsr A                  ; Shift 2 pixels down

L2252:      ldx #$02               ; A2 02
            stx L0089              ; 86 89
            bit L0089              ; 24 89
            beq L225D              ; F0 03
            and #$01               ; 29 01
            asl A                  ; 0A

L225D:      ldx L0049              ; Get movement man
            cpx #$01               ; Man on ladder?
            bne L226C              ; No

            ldx L0047              ; Get man y-dir
            bne L2272              ; Man is moving vertical

            lda #$00               ; Man is moving horizontal
            jmp L2272

L226C:      ldx L0046              ; Get man x-dir
            bne L2272              ; Man is moving vertical
            lda #$00

L2272:      clc                    ; Calculate next sprite
            adc L0088
            sta L0048              ; Set current man sprite
            jsr L23AD              ; Plot man
            ldx L0042              ; Get x-pos man in bytes
            ldy L0043              ; Get y-pos man in bytes
            lda L0045              ; Get ypos man mod 8
            cmp #$04               ; Check if man in upper or lower half tile
            bcc L2285              ; Lower half, check tile below
            iny                    ; Upper half, check tile above

L2285:      sty L0089              ; Save y-pointer
            jsr L2487              ; Get background nr
            sta L0088              ; Save background tilenr
            and #$0C               ; Check for egg or seed
            beq L2302              ; No egg or seed
            and #$08
            bne L22D1              ; Was seed
            dec L0039              ; Was egg, decrement counter

	lda #1
	ldy #1
	ldx #1
	jsr sound

;------------------------------------------------
; Erase seed
;------------------------------------------------
            lda L0088              ; Get background value
            lsr A
            lsr A
            lsr A
            lsr A
            clc
            adc L004E
            tax                    ; Calc position in table
            dec L0510,X            ; Mark egg as taken ($ff)

            lda #$04               ; Erase seed sprite
            sta L008F              ; 85 8F
            ldx L0042              ; A6 42
            ldy L0089              ; A4 89
            jsr L238B              ; Erase egg

            lda L0050              ; Calc value to add to score
            lsr A
            lsr A
            clc
            adc #$01
            cmp #$0A
            bcc L22C9              ; If level<36 add (level/4+1)*10

            lda #$0A               ; Add 100 to score
L22C9:      ldx #$05
            jsr L1AB1              ; Update score

            jmp L2302              ; 4C 02 23

;------------------------------------------------
; Erase seed
;------------------------------------------------

L22D1:
	lda #1
	ldy #1
	ldx #1
	jsr sound

            lda L0088              ; Get background value
            lsr A
            lsr A
            lsr A
            lsr A
            clc
            adc L004E
            tax                    ; Calc position in table
            dec L0520,X            ; Mark seed as taken ($ff)

            lda #$03               ; A9 03
            sta L008F              ; 85 8F
            ldx L0042              ; Get x-pos
            ldy L0089              ; Get y-pos
            jsr L239C              ; Erase seed

            lda #$05               ; Add 50 to score
            ldx #$06
            jsr L1AB1              ; Update score

            lda #$14               ; Timer
            sta L001C

L2302:      rts

;------------------------------------------------
; Check tile for falling
; - Carry clear, no wall
; - Carry set, wall
;------------------------------------------------

L2303:      lda L0046              ; Get x-dir man 
            bmi L230B              ; Dir is left
            bne L234A              ; Dir is right
            clc                    ; Man is standing still
            rts

; Man is falling to the left ------------------
L230B:      lda L0040              ; Get x-pos man
            cmp #$01               ; Check left limit screen
            bcc L2389              ; Man on left limit

            lda L0044              ; A5 44
            cmp #$02               ; C9 02
            bcs L2387              ; B0 70
            lda L0047              ; A5 47
            cmp #$02               ; C9 02
            beq L2387              ; F0 6A

            ldx L0042              ; Get x-pos man in bytes
            dex                    ; Point to tile left from man

            ldy L0043              ; Get y-pos man in bytes
            lda L0045              ; Get y-pos man mod 8
            clc 
            adc L0047              ; Add dir-y
            cmp #$08               ; Check upper byte border
            bcc L2332              ; Same tile
            bpl L2331              ; Point to tile above
            dey                    ; Point to tile below
            jmp L2332

L2331:      iny
L2332:      jsr L2487              ; Get background nr
            cmp #$01               ; Check wall
            beq L2389              ; Yes

            lda L0047              ; Get y-dir
            bpl L2387              ; Was up

            ldx L0042              ; Was down, load x-pos man in bytes
            dex                    ; Point to tile left
            iny                    ; Point to tile up
            jsr L2487              ; Get background nr
            cmp #$01               ; Check wall
            beq L2389              ; Was wall
            bne L2387              ; No wall

; Man is falling to the right ------------------
L234A:      lda L0040              ; Check x-man right border
            cmp #120
            bcs L2389              ; Man on right limit

            lda L0044              ; A5 44
            cmp #$05               ; C9 05
            bcc L2387              ; 90 31
            lda L0047              ; A5 47
            cmp #$02               ; C9 02
            beq L2387              ; F0 2B

            ldx L0042              ; Get x-pos man in bytes
            inx                    ; Point to tile right from man

            ldy L0043              ; Get y-pos man in bytes
            lda L0045              ; Get y-pos man mod 8
            clc
            adc L0047              ; Add dir-y
            cmp #$08               ; Check upper byte border
            bcc L2371              ; Same tile
            bpl L2370              ; Point to tile above
            dey                    ; Point to tile below
            jmp L2371

L2370:      iny
L2371:      jsr L2487              ; Get background nr
            cmp #$01               ; Check wall
            beq L2389              ; Yes

            lda L0047              ; Get y-dir
            bpl L2387              ; Was up

            ldx L0042              ; Was down, load x-pos man in bytes
            inx                    ; Point to tile right
            iny                    ; Point to tile up
            jsr L2487              ; Get background nr
            cmp #$01               ; Check wall
            beq L2389              ; Was wall

L2387:      clc                    ; No wall under man while falling
            rts

L2389:      sec                    ; Wall under man while falling
            rts

;------------------------------------------------
; Erase egg at position X
;------------------------------------------------

L238B:      txa                    ; Save x-pos
            pha
            lda #$00
            jsr L249F              ; Erase egg in background

            lda #yellow            ; Color yellow
            sta L007F
            pla                    ; Get x-pos
            tax
            jsr L1B62              ; Erase egg on screen
            rts

;------------------------------------------------
; Erase seed at position X
;------------------------------------------------

L239C:      txa                    ; Save x-pos
            pha
            lda #$00
            jsr L249F              ; Erase seed in background

            lda #red               ; Color magenta
            sta L007F
            pla                    ; Get x-pos
            tax
            jsr L1B62              ; Erase seed on screen
            rts

;------------------------------------------------
; Plot man in A
;------------------------------------------------

L23AD:      ldx #yellow            ; Color yellow
            stx L007F
            jsr L19D7
            ldx L0040              ; Get x-pos
            ldy L0041              ; Get y-pos
            jsr L1987
            jsr L1902
            rts

;------------------------------------------------
; Plot duck in A+$f
;------------------------------------------------

L23BF:      ldx #yellow            ; Color yellow
            stx L007F
            clc
            adc #$0F               ; Add 15 to spritenr
            jsr L19D7
            ldx L0030              ; Get x-pos
            ldy L0031              ; Get y-pos
            jsr L1987
            jsr L1902
            rts

;------------------------------------------------
; Plot bird in A+$15
;------------------------------------------------

L23D4:      ldx #red               ; Color magenta
            stx L007F

            ldx L0088              ; Get pointer
            lda L0419,X            ; Get birdnr
            clc
            adc #$15               ; Add $15
            pha                    ; Save spritenr
            jsr L19D7              ; Calc sprite address
            ldx L0088              ; Get birdnr
            lda L0400,X            ; Get x-pos bird
            ldy L0405,X            ; Get y-pos bird
            tax
            pla
            cmp #$1D               ; If last sprite bird eat
            bcc L23F6
            txa                    ; Sprite is bird stand
            sbc #$08
            tax
L23F6:      jsr L1987              ; Calc screen address
            jsr L1902              ; Plot bird
            rts

;------------------------------------------------
;Erase duck in A +$f
;------------------------------------------------

L23FD:      clc                    ; Add $f to spritenr
            adc #$0F
            jsr L19D7              ; Calc sprite address
            ldx L0030              ; Get duck x-pos
            ldy L0031              ; Get duck y-pos
            jsr L1987              ; Calc screenaddress
            jsr L1B2C              ; Erase duck
            rts

;------------------------------------------------
; Erase Bird in A +$f
;------------------------------------------------

L240E:      ldx L0088              ; Get bird pointer
            lda L0419,X            ; Get Bird nr
            clc
            adc #$15               ; Add $15
            pha
            jsr L19D7
            ldx L0088              ; Get bird pointer
            lda L0400,X            ; Get x-pos
            ldy L0405,X            ; Get y-pos
            tax
            pla
            cmp #$1D               ; Bird eating
            bcc L242C
            txa                    ; x=x-8
            sbc #$08
            tax

L242C:      jsr L1987              ; Calculate screenaddress
            jsr L1B2C              ; Erase bird
            rts

;------------------------------------------------
; Plot elevator low + high
;------------------------------------------------

L2433:      lda L0055              ; Skip if no elevator
            beq L2486

            ldy L0059              ; Get y-pos elevator
            lda L005B
            beq L243F
            ldy L005A

L243F:      sty L0089              ; Save y-pos elevator

            lda #yellow            ; Color yellow
            sta L007F

            lda #$05               ; Erase elevator sprite
            jsr L19D7
            ldx L0058
            ldy L0089
            jsr L1987              ; Calc sprite address
            jsr L1B2C              ; Erase elevator

            inc L0089              ; Move elevator 2 pixels up
            inc L0089
            lda L0089
            cmp #170               ; Top reached (Y=224)?
            bne L2462
            lda #$06               ; Start at bottom (Y=6)
            sta L0089
L2462:      lda #$05               ; Put elevator sprite
            jsr L19D7              ; Calc sprite address
            ldx L0058
            ldy L0089
            jsr L1987              ; Calc screen address
            jsr L1902              ; Plot sprite

            lda L005B              ; Get elevator toggle
            beq L247C
            lda L0089              ; Update y-pos elevator high
            sta L005A
            jmp L2480

L247C:      lda L0089              ; Update y-pos elevator high
            sta L0059

L2480:      lda L005B              ; Toggle elevator high/low
            eor #$FF
            sta L005B
L2486:      rts

;------------------------------------------------
; Get background nr
;------------------------------------------------

L2487:      cpy #$19               ; Check Y-limit
            bcs L249C
            cpx #20                ; Check X-limit
            bcs L249C
            jsr L24AC              ; Next block 1 line below
            bcs L2498

            lda L0600,X            ; Read spritenr upper screen
            rts

L2498:      lda L0700,X            ; Read spritenr lower screen
            rts

L249C:      lda #$00               ; Out of limits, return 0
            rts

;------------------------------------------------
; Store A in temp area
;------------------------------------------------

L249F:      jsr L24AC              ; Y=Y*20
            bcs L24A8              ; Check upper or lower screen
            sta L0600,X            ; Store in lowerscreen
            rts
L24A8:      sta L0700,X            ; Store in upperscreen
            rts

;------------------------------------------------
; Calculate offset in backgroundbuffer
; Exit with carry set=upperscreen, else lowerscreen
;------------------------------------------------

L24AC:      pha                    ; Save A
            sty L008E              ; Calc Y*20
            tya
            asl A
            asl A
            adc L008E
            asl A
            asl A
            php                    ; Save carry
            clc
            sta L008E              ; Set offset
            txa                    ; Add x to offset
            adc L008E
            tax
            bcs L24C3              ; If carry set, upperscreen
            plp                    ; lowerscreen
            pla
            rts

L24C3:      pla
            pla
            rts

;------------------------------------------------
; Update duck position
;------------------------------------------------

L24C6:
            inc L0038              ; Get duck delay 
            lda L0038
            cmp #$08
            bne L24D7

            lda #$00               ; If delay ticker=8, reset
            sta L0038
            lda L0034              ; Get duck sprite
            jmp L23FD              ; Plot duck

L24D7:      cmp #$04               ; If delay ticker=4
            bne L24DE
            jmp L2760

L24DE:      cmp #$01               ; If delay ticker=1
            bne L24E5
            jmp L24E8 

L24E5:
            jmp L2578              ; Update bird position

L24E8:      lda L0034              ; Get duckspritenr (0-1)
            and #$02
            sta L008B

            lda L0035              ; Check if duck in cage
            beq L255C              ; Yes

            lda L0030              ; Check x-pos+4 duck 
            clc
            adc #$04
            cmp L0040              ; Check with man x-pos
            bcs L250C              ; If man right from duck
            inc L0032              ; Inc x-dir duck
            lda L0032              ; Limit to 6
            cmp #$06
            bmi L2505
            dec L0032

L2505:      lda #$00               ; Set duck sprite right
            sta L008B
            jmp L251A

L250C:      dec L0032              ; Man left from duck, dec x-dir duck
            lda L0032              ; Limit to -6
            cmp #$FB
            bpl L2516
            inc L0032

L2516:      lda #$02               ; Set duck sprite left
            sta L008B

L251A:      lda L0041              ; Check y-pos+4 duck
            clc
            adc #$04
            cmp L0031              ; Check with man y-pos
            bcc L2530              ; If man above duck
            inc L0033              ; Inc y-dir duck
            lda L0033              ; Limit to 6
            cmp #$06
            bmi L252D
            dec L0033
L252D:      jmp L253A

L2530:      dec L0033              ; Man under duck, dec y-dir duck
            lda L0033              ; Limit to -6
            cmp #$FB
            bpl L253A
            inc L0033

L253A:      lda L0031              ; Check y-dir duck
            clc
            adc L0033
            cmp #32                ; Check lower limit=32
            bcs L254B
            lda L0033              ; Invert y-dir
            eor #$FF
            sta L0033
            inc L0033

L254B:      lda L0030              ; Check x-dir duck
            clc
            adc L0032
            cmp #116               ; Check right limit=112
            bcc L255C
            lda L0032              ; Invert x-dir
            eor #$FF
            sta L0032
            inc L0032

L255C:      lda L0030              ; Get x-pos duck
            clc
            adc L0032              ; Add x-dir duck
            sta L0030              ; Store x-pos duck

            lda L0031              ; Get y-pos duck
            clc
            adc L0033              ; Add y-dir duck
            sta L0031              ; Store y-pos duck

            lda L0034              ; Animate ducksprite
            and #$01
            eor #$01
            ora L008B
            sta L0034
            jsr L23BF              ; Plot duck
            rts

;---------------------------------------------------
; Update bird positions 
;
;     8 4 2 1                  Call 266C - L008D  X
; 0 - 0 0 0 0 - Stand facing right           0    0
; 1 - 0 0 0 1 - Walk facing right            1    1
; 2 - 0 0 1 0 - Stand facing left            2    1
; 3 - 0 0 1 1 - Walk facing left             3    2
; 4 - 0 1 0 0 - Climb 1                      4    1
; 5 - 0 1 0 1 - Climb 2                      5    2
; 6 - 0 1 1 0 - Eat half facing right        6    2
; 7 - 0 1 1 1 - Eat down facing right        7    3
; 8 - 1 0 0 0 - Eat half facing left         8    1
; 9 - 1 0 0 1 - Eat down facing left         9    2
;---------------------------------------------------

L2578:
            dec L0036              ; Decrement delay
            ldx L0036
            bpl L2582
            ldx L0037              ; If 0 reset delay
            stx L0036

L2582:      cpx L0057              ; Check with nr of birds
            bcc L2587
            rts
L2587:
            stx L0088              ; Save nr of birds
            lda L0414,X            ; Get bird sprite
            cmp #$01
            bne L2593
            jmp L26B2              ; Bird walk right

L2593:      bcc L2598              ; Bird left or climbing
            jmp L2679              ; Bird stand right

; Bird left or climbing ------------------------------------------

L2598:
            lda L040A,X            ; Get bird x-pos bytes
            sta L008B
            lda L040F,X            ; Get bird y-pos bytes
            sta L008C

            lda #$00               ; Reset bird spritenr
            sta L008D

            ldx L008B              ; Check floor left
            ldy L008C
            dex
            jsr L2487              ; Get background nr
            and #$01
            beq L25B5              ; Floor left= air or ladder

            sta L008D              ; Bird sprite=walk

L25B5:      ldx L008B              ; Check floor right
            ldy L008C
            inx
            jsr L2487              ; Get background nr
            and #$01
            beq L25C8              ; Floor right= air or ladder

            lda #$02               ; Bird sprite=walk left
            ora L008D
            sta L008D

L25C8:      ldx L008B              ; Check floor below
            ldy L008C

            jsr L2487              ; Get background nr below
            and #$02               ; Check ladder
            beq L25DA              ; Floor below=ladder

            lda #$08               ; Bird sprite=eat left
            ora L008D
            sta L008D

L25DA:      ldx L008B              ; Check floor above
            ldy L008C
            iny
            iny
	iny
            jsr L2487              ; Get background nr
            and #$02
            beq L25ED              ; Floor above is air or ladder

            lda #$04               ; Bird sprite=climb
            ora L008D
            sta L008D

L25ED:      jsr L266C              ; 20 6C 26
            cpx #$01               ; E0 01
            bne L25FE              ; D0 0A

            lda L008D              ; Get sprite nr
            ldx L0088              ; Get bird nr
            sta L041E,X            ; Save ???
            jmp L263E

L25FE:      ldx L0088              ; Get bird nr
            lda L041E,X            ; Get spritenr
            cmp #$04               ; 
            bcs L260C              ; B0 05
            eor #$FC               ; Bird eat/climb -> stand
            jmp L260E

L260C:      eor #$F3               ; Bird stand -> eat

L260E:      and L008D              ; 25 8D
            sta L008D              ; 85 8D
            jsr L266C              ; 20 6C 26
            cpx #$01               ; E0 01
            bne L2623              ; D0 0A

            ldx L0088              ; Get bird nr
            lda L008D              ; Get sprite nr
            sta L041E,X            ; Save ???
            jmp L263E

L2623:      lda L008D              ; Get sprite nr
            sta L008E              ; Save 

L2627:      jsr L1AA0              ; Get random nr
            lda L0066              ; A5 66
            and L008E              ; 25 8E
            sta L008D              ; 85 8D
            jsr L266C              ; 20 6C 26
            cpx #$01               ; E0 01
            bne L2627              ; D0 F0

            ldx L0088              ; A6 88
            lda L008D              ; A5 8D
            sta L041E,X            ; 9D 1E 04

L263E:      ldx L0088              ; A6 88
            lda L041E,X            ; BD 1E 04
            and #$03               ; 29 03
            beq L26B2              ; F0 6B
            and #$01               ; 29 01
            beq L2656              ; F0 0B

            ldx L008B              ; Get background left from bird
            ldy L008C
            dex
	iny                        ; UPDATE FOR EATING SEED LEFT
            jsr L2487              ; Get background nr
            jmp L265E

L2656:      ldx L008B              ; Get background right from bird
            ldy L008C
            inx
	iny                        ; UPDATE FOR EATING SEED RIGHT
            jsr L2487              ; Get background nr

L265E:      and #$08               ; Check if background=seed
            beq L26B2              ; No seed

            ldx L0088              ; Update bird sprite
            lda #$02
            sta L0414,X
            jmp L26B2

;------------------------------------------------
; Check nr of 1's in spritenr.
;------------------------------------------------

L266C:      ldx #$00               ; A2 00
            lda L008D              ; A5 8D
L2670:      lsr A                  ; 4A
            bcc L2674              ; 90 01
            inx                    ; E8
L2674:      cmp #$00               ; C9 00
            bne L2670              ; D0 F8
            rts                    ; 60

; Bird right ---------------------------------------------

L2679:      cmp #$04               ; C9 04
            bne L26B2              ; D0 35
            lda L041E,X            ; BD 1E 04
            ldy L040A,X            ; BC 0A 04
            sty L008B              ; 84 8B
            ldy L040F,X            ; BC 0F 04

	iny                        ; UPDATE ERASE SEED RIGHT
            sty L008C              ; Save Y
            ldx L008B
            dex
            and #$01               ; 29 01
            bne L2693              ; D0 02
            inx                    ; E8
            inx                    ; E8
L2693:      stx L008D              ; Save X
            jsr L2487              ; Get background nr
            sta L0089
            and #$08               ; Check if background=seed
            beq L26B2              ; No seed

            lda L0089              ; Calculate seed pointer
            lsr A
            lsr A
            lsr A
            lsr A
            clc
            adc L004E
            tax
            dec L0520,X            ; Mark seed as taken
            ldx L008D
            ldy L008C
            jsr L239C              ; Erase seed

L26B2:      jsr L240E              ; Plot bird
            ldx L0088              ; Get bird nr
            lda L0414,X            ; Get bird sprite
            cmp #$02               ; Bird stand left?
            bcs L2738              ; No, was bird right

            lda L041E,X            ; BD 1E 04
            lsr A                  ; 4A
            bcs L26F6              ; B0 32
            lsr A                  ; 4A
            bcs L270C              ; B0 45
            lsr A                  ; 4A
            bcs L26E0              ; B0 16

            lda L0405,X            ; BD 05 04
            sec                    ; 38
            sbc #$04               ; E9 04
            sta L0405,X            ; 9D 05 04
            lda L0414,X            ; BD 14 04
            beq L26DB              ; F0 03
            dec L040F,X            ; DE 0F 04
L26DB:      lda #$04               ; A9 04
            jmp L2722              ; 4C 22 27

L26E0:      lda L0405,X            ; BD 05 04
            clc                    ; 18
            adc #$04               ; 69 04
            sta L0405,X            ; 9D 05 04
            lda L0414,X            ; BD 14 04
            beq L26F1              ; F0 03
            inc L040F,X            ; FE 0F 04
L26F1:      lda #$04               ; A9 04
            jmp L2722              ; 4C 22 27

L26F6:      lda L0400,X            ; BD 00 04
            sec                    ; 38
            sbc #$04               ; E9 04
            sta L0400,X            ; 9D 00 04
            lda L0414,X            ; BD 14 04
            beq L2707              ; F0 03
            dec L040A,X            ; DE 0A 04
L2707:      lda #$02               ; A9 02
            jmp L2722              ; 4C 22 27

L270C:      lda L0400,X            ; BD 00 04
            clc                    ; 18
            adc #$04               ; 69 04
            sta L0400,X            ; 9D 00 04
            lda L0414,X            ; BD 14 04
            beq L271D              ; F0 03
            inc L040A,X            ; FE 0A 04
L271D:      lda #$00               ; A9 00
            jmp L2722              ; 4C 22 27
L2722:      sta L0419,X            ; 9D 19 04
            lda L0414,X            ; BD 14 04
            eor #$01               ; 49 01
            sta L0414,X            ; 9D 14 04
            clc                    ; 18
            adc L0419,X            ; 7D 19 04
            sta L0419,X            ; 9D 19 04
            jsr L23D4              ; 20 D4 23
            rts                    ; 60

L2738:      lda L0414,X            ; BD 14 04
            asl A                  ; 0A
            and #$1F               ; 29 1F
            sta L0414,X            ; 9D 14 04
            beq L2745              ; F0 02
            lda #$06               ; A9 06
L2745:      ldy L041E,X            ; BC 1E 04
            cpy #$01               ; C0 01
            bne L274F              ; D0 03
            clc                    ; 18
            adc #$02               ; 69 02
L274F:      ldy L0414,X            ; BC 14 04
            cpy #$08               ; C0 08
            bne L2759              ; D0 03
            clc                    ; 18
            adc #$01               ; 69 01
L2759:      sta L0419,X            ; 9D 19 04
            jsr L23D4              ; 20 D4 23
            rts                    ; 60

;------------------------------------------------
; Update timer
;------------------------------------------------

L2760:
            lda #red               ; Color magenta
            sta L007F
            lda L001C
            beq L276B
            dec L001C              ; If timer counter>0 decrement
            rts

L276B:      ldx #$02               ; A2 02
            stx L0088              ; 86 88
L276F:      jsr L27C5              ; 20 C5 27
            ldx L0088              ; A6 88
            dec L001D,X            ; D6 1D
            php                    ; 08
            bpl L277D              ; 10 04
            lda #$09               ; A9 09
            sta L001D,X            ; 95 1D
L277D:      jsr L27C5              ; 20 C5 27
            dec L0088              ; C6 88
            plp                    ; 28
            bmi L276F              ; 30 EA
            clc                    ; 18
            lda L001D              ; A5 1D
            adc L001E              ; 65 1E
            adc L001F              ; 65 1F
            bne L2791              ; D0 03
            inc L004F              ; E6 4F
            rts                    ; 60

L2791:      lda L001F              ; A5 1F
            beq L279A              ; F0 05
            cmp #$05               ; C9 05
            beq L279A              ; F0 01
            rts                    ; 60

L279A:      lda L003D              ; A5 3D
            beq L279F              ; F0 01
            rts                    ; 60

;------------------------------------------------
; Update bonus
;------------------------------------------------

L279F:      ldx #$02               ; A2 02
            stx L0088              ; 86 88

L27A3:      jsr L27D8              ; 20 D8 27
            ldx L0088              ; A6 88
            dec L003A,X            ; D6 3A
            php                    ; 08
            bpl L27B1              ; 10 04
            lda #$09               ; A9 09
            sta L003A,X            ; 95 3A
L27B1:      jsr L27D8              ; 20 D8 27
            dec L0088              ; C6 88
            plp                    ; 28
            bmi L27A3              ; 30 EA
            clc                    ; 18
            lda L003A              ; A5 3A
            adc L003B              ; 65 3B
            adc L003C              ; 65 3C
            bne L27C4              ; D0 02
            inc L003D              ; E6 3D
L27C4:      rts                    ; 60

L27C5:      lda L0088              ; Update time
            tay                    ; A8
            asl A                  ; 0A
            asl A                  ; 0A
            adc #116               ; 69 91
            tax                    ; AA
            lda L001D,Y            ; Get time digit
            ldy #178               ; A0 E7
            jsr L1AFD              ; 20 FD 1A
            rts                    ; 60

L27D8:      lda L0088              ; Update bonus
            tay                    ; A8
            asl A                  ; 0A
            asl A                  ; 0A
            adc #82               ; 69 66
            tax                    ; AA
            lda L003A,Y            ; Get bonus digit
            ldy #178
            jsr L1AFD              ; Print
            rts

L27EB:      lda L0057              ; A5 57
            beq L281B              ; F0 2C
            lda #$00               ; A9 00
            sta L008A              ; 85 8A
L27F3:      ldx L008A              ; A6 8A
            lda L0400,X            ; BD 00 04
            sec                    ; 38
            sbc L0040              ; E5 40
            clc                    ; 18
            adc #$05               ; 69 05
            cmp #$0B               ; C9 0B
            bcs L2813              ; B0 11
            lda L0405,X            ; BD 05 04
            sec                    ; 38
            sbc #$01               ; E9 01
            sbc L0041              ; E5 41
            clc                    ; 18
            adc #$0E               ; 69 0E
            cmp #$1D               ; C9 1D
            bcs L2813              ; B0 02
            inc L004F              ; E6 4F
L2813:      inc L008A              ; E6 8A
            lda L008A              ; A5 8A
            cmp L0057              ; C5 57
            bcc L27F3              ; 90 D8
L281B:      lda L0035              ; A5 35
            beq L283E              ; F0 1F
            lda L0030              ; A5 30
            clc                    ; 18
            adc #$04               ; 69 04
            sec                    ; 38
            sbc L0040              ; E5 40
            clc                    ; 18
            adc #$05               ; 69 05
            cmp #$0B               ; C9 0B
            bcs L283E              ; B0 10
            lda L0031              ; A5 31
            sec                    ; 38
            sbc #$05               ; E9 05
            sbc L0041              ; E5 41
            clc                    ; 18
            adc #$0E               ; 69 0E
            cmp #$1D               ; C9 1D
            bcs L283E              ; B0 02
            inc L004F              ; E6 4F
L283E:      rts                    ; 60

;------------------------------------------------
; Calculate address high score from X in $76/$77
;------------------------------------------------

L283F:      lda #$00
            sta L0077
            dex
            txa
            asl A
            asl A
            asl A
            rol L0077
            asl A
            rol L0077
            clc
            adc #$30
            sta L0076
            lda L0077
            adc #$04
            sta L0077
            rts

;------------------------------------------------
; Fill 10x high score names with A&F
; $430 0,0,0,0,1,0,0,0,A&F.....
; $440 0,0,0,0,1,0,0,0,A&F.....
;  ..             ..
; $4C0 0,0,0,0,1,0,0,0,A&F.....
;------------------------------------------------

L2859:      lda #$0A               ; A9 0A
            sta L008A              ; 85 8A

L285D:      ldx L008A              ; A6 8A
            jsr L283F              ; 20 3F 28
            ldy #$0F               ; A0 0F
            lda #" "               ; A9 20
L2866:      sta (L0076),Y          ; 91 76
            dey                    ; 88
            cpy #$0A               ; C0 0A
            bne L2866              ; D0 F9
            lda #$46               ; A9 46
            sta (L0076),Y          ; 91 76
            dey                    ; 88
            lda #$26               ; A9 26
            sta (L0076),Y          ; 91 76
            dey                    ; 88
            lda #$41               ; A9 41
            sta (L0076),Y          ; 91 76
            dey                    ; 88
            lda #$00               ; A9 00
L287E:      sta (L0076),Y          ; 91 76
            dey                    ; 88
            bpl L287E              ; 10 FB
            lda #$01               ; A9 01
            ldy #$04               ; A0 04
            sta (L0076),Y          ; 91 76
            dec L008A              ; C6 8A
            bne L285D              ; D0 D0
            rts                    ; 60
;------------------------------------------------
; Lookup score in High Score table
; - Fill in score
; - Erase name
;------------------------------------------------

L288E:      lda #$01               ; Entry High score table
            sta L008A

L2892:      ldx L008A
            jsr L283F              ; Calc High Score address in X

            ldy #$00               ; Compare score with High Score
L2899:      lda (L0076),Y          ; B1 76
            cmp L0028,Y            ; D9 28 00
            bmi L28B0              ; 30 10
            bne L28A7              ; D0 05
            iny                    ; C8
            cpy #$08               ; C0 08
            bne L2899              ; D0 F2
L28A7:      inc L008A              ; E6 8A
            lda L008A              ; A5 8A
            cmp #$0B               ; C9 0B
            bcc L2892              ; 90 E3
            rts                    ; 60

L28B0:      jsr L28C9              ; 20 C9 28

            ldy #$07               ; Fill score in High Score table
L28B5:      lda L0028,Y
            sta (L0076),Y
            dey
            bpl L28B5

            ldy #$0F               ; Clear High Score name
            lda #$20
L28C1:      sta (L0076),Y
            dey
            cpy #$07
            bne L28C1
            rts

;------------------------------------------------
; Insert new High Score entry
;------------------------------------------------

L28C9:      lda #$09               ; A9 09
            sta L008B              ; 85 8B
L28CD:      ldx L008B              ; A6 8B
            cpx L008A              ; E4 8A
            bcc L28F5              ; 90 22
            jsr L283F              ; Calc High Score address in X

            ldy #$0F               ; A0 0F
L28D8:      lda (L0076),Y          ; B1 76
            sta L0030,Y            ; 99 30 00
            dey                    ; 88
            bpl L28D8              ; 10 F8
            ldx L008B              ; A6 8B
            inx                    ; E8
            jsr L283F              ; Calc High Score address in X

            ldy #$0F               ; A0 0F
L28E8:      lda L0030,Y            ; B9 30 00
            sta (L0076),Y          ; 91 76
            dey                    ; 88
            bpl L28E8              ; 10 F8
            dec L008B              ; C6 8B
            jmp L28CD              ; 4C CD 28

L28F5:      ldx L008A              ; A6 8A
            jsr L283F              ; Calc High Score address in X
            rts                    ; 60

;------------------------------------------------
; Print intro screen with high scores
;------------------------------------------------

L28FB:      lda #$01
            sta L008A              ; Reset counter

            ldx #<L2A02            ; Print 'HIGH SCORES'
            ldy #>L2A02
            jsr L1A22
L2910:
            lda L008A              ; Set y-pos
            clc
            adc #8
            sta L2A1A+1

            lda #$20               ; Set entry nr
            ldx L008A
            stx L008B
            cpx #$0A
            bne L2927
            lda #$31
            ldx #$00
            stx L008B
L2927:      sta L2A1A+2            ; Set 1st digit entry
L292A:      lda L008B
            clc
            adc #$30
            sta L2A1A+3            ; Set 2nd digit entry

            ldx L008A
            jsr L283F              ; Calc score entry in $76/$77

            ldy #$00               ; Print score
            sty L008B
L293B:      lda (L0076),Y
            bne L2948
            ldx L008B
            bne L2948
            lda #$20               ; Skip leading 0
            jmp L294D
L2948:      clc
            adc #$30
            inc L008B
L294D:
            sta L2A1A+5,y
            iny
            cpy #$08
            bcc L293B

L295A:      lda (L0076),Y
            sta L2A1A+6,y
            iny
            cpy #$10
            bcc L295A

            ldx #<L2A1A            ; Print string $2A1A
            ldy #>L2A1A
            jsr L1A22

            inc L008A              ; If <11, next entry
            lda L008A
            cmp #$0B
            beq L2980
            jmp L2910

L2980:      rts

;------------------------------------------------
; Input High Score name
;------------------------------------------------

L2981:      jsr L288E              ; Look up score in High Score table
            lda L008A
            cmp #$0B               ; If in High Score table branch
            bne L298B
            rts

L298B:      sta L0088              ; Save High Score entry

	clc                        ; Set cursor pos
	adc #8
	sta L2A29+1

L29B3:
            lda L005D              ; Set Playernr
            clc
            adc #$31
            sta L2A2D+9

            lda #<$82a0
            sta $90
            lda #>$82a0
            sta $91
            lda #0
            jsr clear

            ldx #<L2A2C            ; Print 'ENTER YOUR NAME Player '
            ldy #>L2A2C
            jsr L1A22

            jsr L28FB              ; Print High Scores

            ldx #<L2A29            ; Locate cursor and print '>'
            ldy #>L2A29
            jsr L1A22

	ldx #0
	stx tmp_x
L29B5:
	ldy L2A29+1
	lda tmp_x
	clc
	adc #18
	tax
	lda #127
	jsr PUTCHAR

	jsr $fe94   ; Get character
	ldx tmp_x
	sta L2A65,x
	cmp #$0d    ; Return pressed, end input
	beq L29B6
	cmp #$7f    ; Backspace pressed
	beq L2A00

	pha
	ldy L2A29+1
	lda tmp_x
	clc
	adc #18
	tax
	pla
	jsr PUTCHAR

	inc tmp_x
	lda tmp_x
	cmp #9
	bne L29B5
	dec tmp_x
	jmp L29B5
L29B6:
            ldx L0088              ; Calculate High Score table Address
            jsr L283F


            ldy #$08               ; Copy name into High Score table
L29F3:      lda L2A65-8,Y
            cmp #$0D
            beq L2A01
            sta (L0076),Y
            iny
            cpy #$10
            bcc L29F3
L2A01:      rts

L2A00:
	lda tmp_x  ; Handle backspace
	beq L29B5

	ldy L2A29+1
	lda tmp_x
	clc
	adc #18
	tax
	lda #' '
	jsr PUTCHAR
	dec tmp_x
	jmp L29B5

tmp_x:      .db 0

L2A02:      .byte yellow+10,6,'HIGH SCORES',0,$ff

L2A1A:      .byte red+6,7,' 1     1000 A&F     ',0,$ff

L2A21:      .byte $0A
            .byte $12,$00,$03
            .byte $19,$04,$A0,$02

L2A29:      .byte yellow+17,0,'>',0,$ff

L2A2C:      .byte yellow+8,21,'ENTER YOUR NAME',0
L2A2D:      .byte red+12,22,'Player 1',0,$ff

L2A60:      .byte $65,$2A,$08,$20,$7F
L2A65:      .byte $20,$20,$20,$20,$20,$20,$20,$20,$20 ; Name input

;------------------------------------------------
;PROGRAM ENTRY
;------------------------------------------------
program_entry:

L2A6E:
	jsr L2BA5   ; Init
L2A71:
	jsr L2D4A   ; Loop screens until keypress

	jsr clear4
	jsr L2C68   ; Input 'How many players?'

	lda #0      ; HACK--------------------
	sta L0050   ; HACK--------------------

L2A77:
	jsr clear4
	ldx #<L2B80 ; Print 'Get Ready'
	ldy #>L2B80
	jsr L1A22

	ldx #<L2B97 ; Print 'Player '
	ldy #>L2B97
	jsr L1A22

	lda L005D   ; Print playernr
	clc
	adc #$31
	ldx #19
	ldy #12
	jsr PUTCHAR

	lda #$0A    ; Wachtloop
	jsr L2D39
L2A92:
	jsr L2EA5   ; Init level + vars

	jsr L1BB3   ; Draw level
	jsr L2F79   ; Draw sprites

L2AA0:
	jsr L1A37   ; Read keys
	jsr L1EDE   ; Move man

            jsr L33E4              ; Movement sound

            jsr L2433              ; Update elevators
            jsr L24C6              ; Update duck+bird position

            jsr L3030              ; 20 30 30
            jsr L27EB              ; 20 EB 27
            jsr L1B90              ; 20 90 1B
            lda L004F              ; A5 4F
            bne L2B09              ; D0 4D

            lda L0041              ; Get y-pos man
            cmp #17
            bcc L2B09              ; If >17

            lda L0039              ; Check eggs on screen
            beq L2ACD              ; All gone
            lda L0060              ; 
            bmi L2A71              ; 
            jmp L2AA0
L2ACD:
            jsr L2C4F              ; 20 4F 2C
            lda L003D              ; A5 3D
            bne L2AFB              ; D0 27
            lda L003C              ; A5 3C
            beq L2AF6              ; F0 1E

L2AD8:      sta L008A              ; Set counter

            ldx #$06
            jsr L1AB1              ; Update score

L2ADF:      jsr L279F              ; Update bonus
            dec L008A              ; C6 8A
            bne L2ADF              ; D0 F9
            jsr L3030              ; 20 30 30

	lda #5
	ldy #1
	ldx #9
	jsr sound

            lda L003D              ; A5 3D
            bne L2AFB              ; D0 05

L2AF6:      lda #$0A               ; Add 10000 to score
            jmp L2AD8              ; Update score

L2AFB:      inc L0050              ; Increment levelnr
            jsr L2F52              ; Save playerdata
            jsr L2EE5              ; Init playerdata
            jsr L2F14              ; Get playerdata
            jmp L2A92              ; Start new level
L2B09:
            jsr L2C4F              ; Plot birds and duck
            jsr L2F52              ; Save playerdata

; PLAY TUNE MUST BE INSERTED HERE ----------------------------------------------
	jsr L3063

            ldx L005D              ; Get player nr
            dec L0020,X            ; Decrement live
            bne L2B48              ; Check if end game

            ldx #<L2B62            ; Print 'GAME OVER'
            ldy #>L2B62
            jsr L1A22

            ldx #<L2B97            ; Print 'PLAYER'
            ldy #>L2B97
            jsr L1A22

            lda L005D              ; Print player number
            clc
            adc #$31
            ldx #19
            ldy #12
            jsr PUTCHAR

            lda #$0A               ; Wait 1 sec
            jsr L2D39

            jsr L2981              ; Input high score name

            lda #$05               ; Wait 0,5 sec
            jsr L2D39

            dec L005F              ; Decrement playernr
            beq L2B5F              ; Check end game

L2B48:      ldx L005D              ; Set next player nr
            inx
            txa
L2B4C:      and #$03
            sta L005D
            cmp L005E              ; Check overflow max players
            bcs L2B48              ; Next playernr

            tax                    ; Get player nr
            lda L0020,X            ; Get lives
            beq L2B48              ; If zero, next player
            jsr L2F14              ; Get playerdata
            jmp L2A77              ; Start game with next player

L2B5F:      jmp L2A71              ; Game over back to intro

L2B62:      .byte yellow+10,9,'           ',0
            .byte yellow+10,10,' GAME OVER ',0
            .byte yellow+10,11,'           ',0,$ff
L2B80:
            .byte yellow+10,10,' Get Ready ',0,$ff
L2B97:
            .byte blue+10,12,' Player    ',0
            .byte blue+10,13,'           ',0,$ff
 
;------------------------------------------------
; INIT
;
; - Relocate code from $3100-$38ff to $900-$10ff
; - Select MODE 5
; - Set vars
; - Fill high score names $430-$4C0 with 0000100A&F.....
; - Redefine logical colors 0,1,2,3
;------------------------------------------------

L2BA5:
	lda #clearmode             ; Clear4 color
	sta $b000
	jsr clear4

            lda #$00               ; Jump key SPACE
            sta L0065
            lda #$21               ; Up key A
            sta L0064
            lda #$3a               ; Down key Z
            sta L0063
            lda #$1c               ; Left key <
            sta L0062
            lda #$1e               ; Right key >
            sta L0061

            jsr L2859              ; Fill high score names with A&F

	lda #0
	sta L001B              ; Reset joystickflag
	jsr joyinit

            rts

;------------------------------------------------
; Plot birds and duck
;------------------------------------------------

L2C4F:      lda L0048              ; Get spritenr
            jsr L23AD              ; Plot sprite
            lda L0057              ; Get birdnr
            sta L0088
L2C58:      dec L0088
            bmi L2C62
            jsr L23D4              ; Plot bird
            jmp L2C58              ; Next bird

L2C62:      lda L0034              ; Plot duck
            jsr L23BF
            rts

;------------------------------------------------
; Scan for keys 1,2,3,4 and print result
;------------------------------------------------

L2C68:      ldx #<L2D1F            ; Print string
            ldy #>L2D1F
            jsr L1A22

            lda #$00               ; A9 00
            sta L008B              ; 85 8B
            lda #$64               ; A9 64
            sta L008C              ; 85 8C

L2C77:
	lda #$11     ; Key '1'
	jsr scankey
	bcc L2C89    ; no
	lda #$01
	jmp L2CCC

L2C89:
	lda #$12     ; Key '2'
	jsr scankey
	bcc L2C9B    ; no
	lda #$02
	jmp L2CCC

L2C9B:
	lda #$13     ; Key '3'
	jsr scankey
	bcc L2CAD    ; no
	lda #$03
	jmp L2CCC

L2CAD:
	lda #$14     ; Key '4'
	jsr scankey
	bcc L2CBF    ; no
	lda #$04
	jmp L2CCC

L2CBF:      dec L008B              ; Repeat 256000 times
            bne L2C77
            dec L008C
            bne L2C77

            pla                    ; No key pressed, return
            pla
            jmp L2A71

L2CCC:      sta L005E              ; Save player count
            sta L005F
            clc
            adc #$30

	ldx #24 ; Print selection
	ldy #12
	jsr PUTCHAR

            lda #$05               ; Wait 0,5 sec
            jsr L2D39

;------------------------------------------------
; Fill player table at $500
;------------------------------------------------

L2CDB:      ldx #$03
L2CDD:      lda #$00               ; Level=0
            sta L0024,X
            lda #$05               ; Lives=5
            sta L0020,X
            dex
            bpl L2CDD

            ldx #$03               ; A2 03
            stx L0088              ; 86 88
L2CEC:      txa                    ; 8A
            asl A                  ; 0A
            asl A                  ; 0A
            asl A                  ; 0A
            asl A                  ; 0A
            asl A                  ; 0A
            asl A                  ; 0A
            tax                    ; AA
            ldy #$07               ; A0 07
            lda #$00               ; A9 00
L2CF8:      sta L0500,X            ; 9D 00 05
            inx                    ; E8
            dey                    ; 88
            bpl L2CF8              ; 10 F9
            dec L0088              ; C6 88
            ldx L0088              ; A6 88
            bpl L2CEC              ; 10 E7

            lda #$00               ; Init levelnr
            sta L0050
            lda #$04               ; Init max players
            sta L005D
L2D0D:      dec L005D              ; C6 5D
            jsr L2EE5              ; 20 E5 2E
            lda L005D              ; A5 5D
            bne L2D0D              ; D0 F7
            jsr L2F14              ; 20 14 2F

            lda #$1A               ; Restore default window
            rts                    ; 60

;------------------------------------------------
;------------------------------------------------
L2D1F:      .byte yellow+6,12,'How many players? ',0,$ff

;------------------------------------------------
; Wait loop A * 0,1 sec
;------------------------------------------------

L2D39:      sta L008A              ; $85,$8A
L2D3B:      ldy #$00               ; A0 00
            ldx #$00               ; A2 00
L2D3F:      dex                    ; CA
            bne L2D3F              ; D0 FD
            dey                    ; 88
            bne L2D3F              ; D0 FA
            dec L008A              ; C6 8A
            bne L2D3B              ; D0 F2
            rts                    ; 60

;------------------------------------------------
; Loop screens until keypress
; - Introscreen High Score list
; - Random level
; - Introscreen keys
; - Random level
; - Pause between screen ca.6 sec
;------------------------------------------------

L2D4A:
	jsr L2DB3   ; Set vars

L2D50:
	jsr clear4  ; Clear screen
	jsr L2DC0   ; Print CHUCKIE EGG
	jsr L28FB   ; Print High Score list
	jsr L2E1F   ; Print footer intro screen

	lda #15     ; Wait ca.6 sec
	sta L008A
L2D62:
	jsr L2E8B   ; Scan for K and S
	bcs L2DA0
	dec L008A
	bne L2D62

	jsr L2DA1   ; Show gamelevel

	lda #15     ; Wait for ca.6 sec
	sta L008A
L2D70:
	jsr L2E8B   ; Scan for K and S
	bcs L2DA0
	dec L008A
	bne L2D70

	jsr clear4
	jsr L2DC0   ; Print CHUCKIE EGG
	jsr L3100   ; Print keys in use

	jsr L2E1F   ; Print footer intro screen
	lda #15     ; Wait ca.6 sec
	sta L008A
L2D89:
	jsr L2E8B   ; Scan for K and S
	bcs L2DA0
	dec L008A
	bne L2D89

	jsr L2DA1   ; Show gamelevel

	lda #15     ; Wait for ca.6 sec
	sta L008A
L2D97:
	jsr L2E8B   ; Scan for K and S
	bcs L2DA0
	dec L008A
	bne L2D97
L2D9E:
	jmp L2D50

L2DA0:
	rts
;------------------------------------------------
; Show gamelevel
;------------------------------------------------

L2DA1:      jsr L1AA0              ; Get random levelnr
            lda L0066
            and #$07
            sta L0050              ; Levelnr
            sta L005C
            jsr L1BB3              ; Draw level
            jsr L2F79              ; Draw sprites
            rts

;------------------------------------------------
; Set max players to 4 and create table
;------------------------------------------------

L2DB3:      lda #$04
            sta L005E              ; Max players
            sta L005F              ; Max players
            jsr L2CDB              ; Fill 4 player table
            jsr L2EA5              ; Init level + vars
            rts

;------------------------------------------------
; Print CHUCKIE EGG on screen
;------------------------------------------------

L2DC0:      lda #yellow               ; Color yellow
            sta L007F

            lda #$30               ; Letter C
            ldx #$00
            ldy #184
            jsr L2E99

            lda #$31               ; Letter H
            ldx #13
            ldy #184
            jsr L2E99

            lda #$32               ; Letter U
            ldx #25
            ldy #184
            jsr L2E99

            lda #$30               ; Letter C
            ldx #38
            ldy #184
            jsr L2E99

            lda #$33               ; Letter K
            ldx #51
            ldy #184
            jsr L2E99

            lda #$34               ; Letter I
            ldx #64
            ldy #184
            jsr L2E99

            lda #$35               ; Letter E
            ldx #69
            ldy #184
            jsr L2E99

            lda #$35               ; Letter E
            ldx #90
            ldy #184
            jsr L2E99

            lda #$36               ; Letter G
            ldx #103
            ldy #184
            jsr L2E99

            lda #$36               ; Letter G
            ldx #116
            ldy #184
            jsr L2E99
            rts


;------------------------------------------------
; Print footer in intro screen
;------------------------------------------------

L2E1F:      ldx #<L2E27            ; Print footer
            ldy #>L2E27
            jsr L1A22
            rts

L2E27:   ;Press fire or S to start
           .byte yellow+9,22,' tart, or ',0
           .byte red+9,22,'S',0
           .byte red+19,22,'Fire',0

           .byte yellow+8,23,'  to change keys',0
           .byte red+8,23,'K',0
           .byte $ff

;------------------------------------------------
; Wait keypress K or S or fire
;------------------------------------------------

L2E63:
	lda #$33    ; Key "S"
	jsr scankey
	bcc L2E74   ; no
	sec
	rts

L2E74:
	lda #$2b    ; Key "K"
	jsr scankey
	bcc L2E82   ; no
	jsr L3103  ; Redefine keys
	pla
	pla
	jmp L2D50
L2E82:
	jsr joyget  ; Scan firebutton joystick
	and #$10
	beq L2E75   ; no
	lda #1      ; Set joystickflag
	sta L001B
	sec
	rts
L2E75:
	clc
	rts

;------------------------------------------------
; Scan for S or K and wait ca. 6 sec
;------------------------------------------------

L2E8B:
            ldy #$ff
L2E92:
            jsr L2E63              ; Scan keys
	bcs L2E93

            ldx #$e0               ; Wait
L2E94:
            dex
            bne L2E94
            dey
            bne L2E92
L2E93:
            rts

;------------------------------------------------
; Plot sprite A at X,Y
;------------------------------------------------

L2E99:      pha                    ; Save spritenr
            jsr L1987              ; Calc Screen address  $70/$71
            pla                    ; Get Spritenr
            jsr L19D7              ; Calc Sprite adddress $76/$77
            jsr L1902              ; Plot sprite
            rts

;------------------------------------------------
; Init level + vars
;------------------------------------------------

L2EA5:      lda L0050              ; Get levelnr
            and #$07
            sta L005C              ; Levelnibble low

            lda L0050              ; Get levelnr
            lsr A
            lsr A
            lsr A
            sta L004D              ; Levelnibble high

            lda #$00               ; Check levelnr
            sta L0035
            lda L004D
            beq L2EBC              ; Level 1-8 Duck in cage
            inc L0035              ; Level >8 Duck out cage

L2EBC:      lda #$01
            sta L0038

            lda #$00               ; Reset bird delay
            sta L0036

            lda #$07
            ldx L004D              ; Levelnibble high
            cpx #$04               ; Level 33 onwards
            bcc L2ECE
            lda #$05
L2ECE:      sta L0037              ; Bird delay=7 or 5 (level>32)

            lda #$00               ; Reset
            sta L003E              ; ??
            sta L004F              ; ??
            sta L001C              ; Timer
            sta L008F              ; ??

            lda #$76               ; ??
            sta L0066              ; ??
            sta L0067              ; ??
            sta L0068              ; ??
            sta L0069              ; ??
            rts                    ; 60

;------------------------------------------------
; Init savedata player
;------------------------------------------------

L2EE5:      lda L005D              ; Get playernr
            asl A
            asl A
            asl A
            asl A
            asl A
            asl A
            tax                    ; Point to savedata

            lda L0050              ; Get levelnr
            clc
            adc #$01
            cmp #$0A               ; If >10 store levelnr
            bcc L2EF9
            lda #$09               ; Else store 9
L2EF9:      sta L0508,X            ; Store bonus
            lda #$00
            sta L0509,X
            sta L050A,X
            sta L050B,X

            ldy #$10
L2F09:      sta L0510,X            ; Clear eggs flags
            sta L0520,X            ; Clear seeds flag
            inx
            dey
            bne L2F09
            rts

;------------------------------------------------
; Get playerdata player x
; - Levelnr
; - Score
; - Bonus
;------------------------------------------------

L2F14:      ldx L005D              ; Current playernr
            lda L0024,X            ; Get levelnr
            sta L0050              ; Save levelnr

            txa
            asl A
            asl A
            asl A
            asl A 
            asl A
            asl A
            sta L004E              ; Savepos player x
            tax                    ; x=Playernr*64

            ldy #$00
L2F26:      lda L0500,X            ; Get saved player score
            sta L0028,Y            ; Store into current Score
            inx
            iny
            cpy #$08
            bcc L2F26

            ldx L004E
            ldy #$00
L2F36:      lda L0508,X            ; Get saved player bonus
            sta L003A,Y            ; Store into current bonus
            inx
            iny
            cpy #$04
            bcc L2F36

            ldx L005D              ; $3F=left lives position player
            lda #$00
            clc
L2F47:      adc #26
            dex
            bpl L2F47
            sec
            sbc #9+4
            sta L003F
            rts

;------------------------------------------------
; Save playerdata player x
; - Levelnr
; - Score
; - Bonus
;------------------------------------------------

L2F52:      ldx L005D              ; Save current levelnr
            lda L0050
            sta L0024,X

            ldx L004E              ; Save score
            ldy #$00
L2F5C:      lda L0028,Y
            sta L0500,X
            inx
            iny
            cpy #$08
            bcc L2F5C

            ldx L004E              ; Save bonus
            ldy #$00
L2F6C:      lda L003A,Y
            sta L0508,X
            inx
            iny
            cpy #$04
            bcc L2F6C
            rts

;------------------------------------------------
; Draw sprites
;------------------------------------------------

; Plot elevator --------------------------------------------

L2F79:      lda L0055              ; A5 55
            beq L2FAB              ; F0 2E
 
            lda #$08               ; y-pos elevator low
            sta L0059
            lda #$5A               ; y-pos elevator high
            sta L005A
            lda #$00               ; elevator flag
            sta L005B

            lda #yellow            ; Color yellow
            sta L007F
            lda #$05               ; Elevator sprite
            jsr L19D7
            ldx L0058
            ldy L0059              ; y=8
            jsr L1987
            jsr L1902              ; Plot elevator1

            lda #$05               ; Elevator sprite
            jsr L19D7
            ldx L0058
            ldy L005A              ; y=90
            jsr L1987
            jsr L1902              ; Plot elevator2

; Plot duck ------------------------------------------------

L2FAB:      lda #$04               ; x-pos duck
            sta L0030
            lda #154               ; y-pos duck
            sta L0031
            lda #$00               ; A9 00
            sta L0032              ; 85 32
            sta L0033              ; 85 33
            sta L0034              ; 85 34
            jsr L23BF              ; 20 BF 23

; Plot birds ------------------------------------------------

            ldx #$FF               ; A2 FF
            stx L0088              ; 86 88

            lda L004D              ; Load levelnibble high
            cmp #$01               ; Level between 9 and 16?
            bne L2FCC
            ldx #$00               ; 0 birds
            stx L0057

L2FCC:      cmp #$03               ; Level > 25?
            bcc L2FD4
            ldx #$05               ; 5 birds
            stx L0057

L2FD4:      inc L0088              ; E6 88
            ldx L0088              ; A6 88
            cpx L0057              ; Nr of birds =0?
            bcs L3004

            lda L040A,X            ; Load x-pos bird
            asl A
            asl A
            asl A
            sta L0400,X            ; Store x-pos*16

            lda L040F,X            ; Load y-pos bird
            asl A
            asl A
            asl A
            clc
            adc #$14               ; Store y-pos+20
            sta L0405,X

            lda #$00               ; Reset birdnr
            sta L0414,X
            sta L0419,X

            lda #$02               ; A9 02
            sta L041E,X            ; 9D 1E 04
            jsr L23D4              ; 20 D4 23
            jmp L2FD4              ; 4C D4 2F

; Plot man ------------------------------------------------

L3004:
            lda #$03               ; Wait 0,3 sec
            jsr L2D39
L3005:
            lda #$3C-8            ; RC3 for all levels
L3006:
            sta L0040              ; x-pos man
            lda #$18               ; y-pos man
            sta L0041              ; 85 41

L3011:      lda #$06               ; Man stand right
            sta L0048
            jsr L23AD              ; Plot sprite

	lda L0040
	clc	
	adc #$03
	and #7
	sta L0044                  ; Set x-pos man mod 8
	lda L0040
	lsr a
	lsr a
	lsr a
	sta L0042                  ; Set x-pos man bytes

            lda #$02
            sta L0043              ; Set y-pos man bytes

            lda #$00
            sta L0045              ; Set y-pos man mod 8
            sta L0049              ; Man moving horizontal

; Erase life ------------------------------------------------
            lda #$01
            sta L004C
            jsr L3041              ; Erase life
            rts

;------------------------------------------------
;------------------------------------------------

L3030:
            lda L003E              ; Get ?????
            bne L3035
            rts

L3035:
            lda #$00               ; Reset ??
            sta L003E
            jsr L3041              ; Plot lives left

            ldx L005D              ; Get playernr
            inc L0020,X            ; Increment live
            rts

;------------------------------------------------
; Plot lives left (max 6)
;------------------------------------------------

L3041:      lda #yellow            ; Color yellow
            sta L007F
            ldx L005D
            lda L0020,X            ; Load nr of lives for current player
            cmp #$06               ; Max 6
            bcc L304E 
            rts

L304E:      asl A                  ; Calculate lives position
            asl A 
            adc L003F
	adc #7
            tax
            ldy #182               ; y=182
            jsr L1987
            lda #$2F               ; Lives sprite
            jsr L19D7
            jsr L1B82              ; Plot sprite
            rts

;------------------------------------------------
; Play sound pointed at in X,Y
;------------------------------------------------

L3063:
	lda #0
	sta $80
tune_loop:
	ldx $80
	lda L308D,x
	pha
	lda L308D+1,x
	pha
	lda L308D+2,x
	tay
	pla
	tax
	pla
	jsr sound
	inc $80
	inc $80
	inc $80
	lda $80
	cmp #48
	bne tune_loop
	rts

;------------------------------------------------
; Sound data die tune
; 1st byte is tone, 2nd byte is duration
;------------------------------------------------

L308D:
	.db 40,18,4  ; G''4
	.db 20,16,4  ; A''2
	.db 40,18,4  ; G''4
	.db 20,20,4  ; F''2
	.db 40,22,4  ; E''4
	.db 20,28,4  ; C''2
	.db 40,24,4  ; D''4
	.db 20,14,8  ; B'2
	.db 120,28,4 ; C''12
	.db 10,28,4  ; C''1
	.db 10,24,4  ; D''1
	.db 10,22,4  ; E''1
	.db 10,20,4  ; F''1
	.db 10,18,4  ; G''1
	.db 10,29,2  ; B''1
	.db 10,28,2  ; C'''1

;            .byte $10 ; 16 tones
;            .byte $21,$04 ; G''4
;            .byte $29,$02 ; A''2
;            .byte $21,$04 ; G''4
;            .byte $19,$02 ; F''2
;            .byte $15,$04 ; E''4
;            .byte $05,$02 ; C''2
;            .byte $0D,$04 ; D''4
;            .byte $01,$02 ; B'2
;            .byte $05,$0C ; C''12
;            .byte $05,$01 ; C''1
;            .byte $0D,$01 ; D''1
;            .byte $15,$01 ; E''1
;            .byte $19,$01 ; F''1
;            .byte $21,$01 ; G''1
;            .byte $31,$01 ; B''1
;            .byte $35,$01 ; C'''1

;------------------------------------------------

L30AE:      .byte $01,$01,$00,$00,$00,$00,$00
            .byte $00,$7E,$CE,$00,$00,$64,$00,$02
            .byte $01,$00,$00,$00,$00,$00,$00,$7E
            .byte $FE,$00,$FB,$7E,$64,$03,$01,$00
            .byte $00,$00,$00,$00,$00,$32,$00,$00
            .byte $E7,$64,$00

            .byte $0A
            .byte 'Copyright (C) A&F Software Ltd. 1984'
            .byte $0A,$0D,$00

;------------------------------------------------
;Relocatable code from $3100 to $0900
;------------------------------------------------

L3100:      jmp L3344

L3103:
	lda #clearmode             ; Clear screen
	sta $b000
	jsr clear4

	lda #$ff
	sta L0061
	sta L0062
	sta L0063
	sta L0064
	sta L0065

            ldx #<L3272            ; Print KEY SELECTION
            ldy #>L3272
            jsr L1A22

            lda #$00               ; Reset key pressed flag
            sta L0060
            lda #$54               ; 'T'??
            sta L0028

            ldx #<L329C            ; Print Up ..
            ldy #>L329C
            jsr L1A22

            jsr L314F              ; Input key and print on screen
            sta L0064              ; Store key up

            ldx #<L32A9            ; Print down ..
L3120:      ldy #>L32A9
            jsr L1A22
            jsr L314F              ; Input key and print on screen
            sta L0063              ; Store key down

            ldx #<L32B8
            ldy #>L32B8
            jsr L1A22
            jsr L314F              ; Input key and print on screen
            sta L0062              ; Store key left

            ldx #<L32C7
            ldy #>L32C7
            jsr L1A22
            jsr L314F              ; Input key and print on screen
            sta L0061              ; Store key right

            ldx #<L32D7
            ldy #>L32D7
            jsr L1A22
            jsr L314F              ; Input key and print on screen
            sta L0065              ; Store key jump

            rts

;------------------------------------------------
; Redefine keys
;------------------------------------------------

L314E:
	lda #7      ; Beep
	jsr $fff4

L314F:
	jsr waitkey ; Wait for key release
	cpy #$ff
	bne L314F

	lda $b001   ; Wait for release CTRL/SHIFT
	and #$c0
	cmp #$c0
	bne L314F

	lda $b002   ; Wait for release REPT
	and #$40
	beq L314F

	ldy #$ff
L3150:
	lda $b001   ; Scan SHIFT
	and #$80
	bne L315E
	ldy #$82    ; SHIFT pressed
	jmp L3176
L315E:
	lda $b001   ; Scan CTRL
	and #$40
	bne L315F
	ldy #$80    ; CTRL pressed
	jmp L3176
L315F:
	lda $b002   ; Scan REPT
	and #$40
	bne L316D
	ldy #$81    ; REPT pressed
	jmp L3176
L316D:
	jsr waitkey ; Scan any key
	cpy #$ff
	beq L3150   ; Loop if no key pressed

L3176: 
	sty L0089   ; Save key
	tya
	ldy #4
L3177:
	cmp L0061,y ; Check if not in use
	beq L314F
	dey
	bpl L3177

	jmp L31CF   ; Print code

; Print key, add #3A to scancode ---------
L31CF:
	cmp #$01		; Check [
	bne L31D0
L31D2:
	clc
	adc #$3a
	jmp L3265
L31D0:
	cmp #$02		; Check \
	bne L31D1
	jmp L31D2
L31D1:
	cmp #$03		; Check ]
	bne L31D4
	jmp L31D2

; Print key, add #10 to scancode ---------
L31D4:
	cmp #$1c		; Check ,
	bne L31D6
L31D5:
	clc
	adc #$f0
	jmp L3265
L31D6:
	cmp #$1d		; Check -
	bne L31D7
	jmp L31D5
L31D7:
	cmp #$1e		; Check .
	bne L31D8
	jmp L31D5
L31D8:
	cmp #$1f		; Check /
	bne L31D9
	jmp L31D5
L31D9:

; Print key, special keys->print text --

            cmp #$06               ; Check left-right arrow
            bne L3209
	lda YPOS
	sta L330B+1
            ldx #<L330B            ; Print
            ldy #>L330B
            jmp L326C

L3209:      cmp #$07               ; Check up-down arrow
            bne L3214
	lda YPOS
	sta L3316+1
            ldx #<L3316            ; Print
            ldy #>L3316
L3211:      jmp L326C

L3214:      cmp #$04               ; Check up arrow
            bne L321F
	lda YPOS
	sta L332D+1
            ldx #<L332D            ; Print
            ldy #>L332D
            jmp L326C

L321F:      cmp #$05               ; Check lock arrow
            bne L322A
	lda YPOS
	sta L3322+1
            ldx #<L3322            ; Print
            ldy #>L3322
            jmp L326C

L322A:      cmp #$3b               ; Check Escape
            bne L3240
	lda YPOS
	sta L32EB+1
            ldx #<L32EB            ; Print
            ldy #>L32EB
            jmp L326C

L3240:      cmp #$0e               ; Check Copy
            bne L324B
	lda YPOS
	sta L3306+1
            ldx #<L3306            ; Print
            ldy #>L3306
            jmp L326C

L324B:      cmp #$0d               ; Check Return
            bne L3256
	lda YPOS
	sta L32FF+1
            ldx #<L32FF            ; Print
            ldy #>L32FF
            jmp L326C

L3256:      cmp #$0f               ; Check Delete
            bne L3261
	lda YPOS
	sta L32F8+1
            ldx #<L32F8            ; Print
            ldy #>L32F8
            jmp L326C

L3261:      cmp #$00               ; Check Space
            bne L3262
	lda YPOS
	sta L32F2+1
            ldx #<L32F2            ; Print
            ldy #>L32F2
            jmp L326C

L3262:      cmp #$80               ; Check Control
            bne L3263
	lda YPOS
	sta L333C+1
            ldx #<L333C            ; Print
            ldy #>L333C
            jmp L326C

L3263:      cmp #$81               ; Check Rept
            bne L3264
	lda YPOS
	sta L3337+1
            ldx #<L3337            ; Print
            ldy #>L3337
            jmp L326C

L3264:      cmp #$82               ; Check Shift
            bne L3265
	lda YPOS
	sta L3336+1
            ldx #<L3336            ; Print
            ldy #>L3336
            jmp L326C

; Print key, add #20 to scancode ---------
L3265:
	clc                        ; Print '+ Key +'
	adc #$20
	pha
	lda #$27
	ldy YPOS
	ldx #14
	jsr PUTCHAR
	pla
	ldy YPOS
	ldx #15
	jsr PUTCHAR
	lda #$27
	ldy YPOS
	ldx #16
	jsr PUTCHAR

            jmp L326F

L326C:      jsr L1A22              ; Print string

L326F:
            lda L0089
            rts

;------------------------------------------------
; Textstrings
;------------------------------------------------

L3272:      .byte yellow+13,1,'K E Y',0
            .byte yellow+7,3,'S E L E C T I O N',0,$ff

L329C:      .byte red+8,8,'Up .. ',0,$ff

L32A9:      .byte red+6,10,'Down .. ',0,$ff

L32B8:      .byte red+6,12,'Left .. ',0,$ff

L32C7:      .byte red+5,14,'Right .. ',0,$ff

L32D7:      .byte red+6,16,'Jump .. ',0,$ff

L32EB:      .byte red+14,12,'Escape',0,$ff

L32F2:      .byte red+14,12,'Space',0,$ff

L32F8:      .byte red+14,12,'Delete',0,$ff

L32FF:      .byte red+14,12,'Return',0,$ff

L3306:      .byte red+14,12,'Copy',0,$ff

L330B:      .byte red+14,12,'Curs-Hor',0,$ff

L3316:      .byte red+14,12,'Curs-Vert',0,$ff

L3322:      .byte red+14,12,'Lock',0,$ff

L332D:      .byte red+14,12,'Up Arrow',0,$ff

L3336:      .byte red+14,12,'Shift',0,$ff

L3337:      .byte red+14,14,'Rept',0,$ff

L333C:      .byte red+14,10,'Control',0,$ff

L333D:      .byte red+14,10,'[',0,$ff

L333E:      .byte red+14,10,'\',0,$ff

L333F:      .byte red+14,10,']',0,$ff

;------------------------------------------------
; Print keys in use
;------------------------------------------------

L3344:
            ldx #<L33A4  ; Print KEYS
            ldy #>L33A4
            jsr L1A22

            ldx #<L329C  ; Print 'UP .. '
            ldy #>L329C
            jsr L1A22

            lda L0064    ; Print key in use
            jsr L339C

            ldx #<L32A9  ; Print 'DOWN .. '
            ldy #>L32A9
            jsr L1A22

            lda L0063    ; Print key in use
            jsr L339C

            ldx #<L32B8  ; Print 'LEFT .. '
            ldy #>L32B8
            jsr L1A22

            lda L0062    ; Print key in use
            jsr L339C

            ldx #<L32C7  ; Print 'RIGHT .. '
            ldy #>L32C7
            jsr L1A22

            lda L0061    ; Print key in use
            jsr L339C

            ldx #<L32D7  ; Print 'JUMP .. '
            ldy #>L32D7
            jsr L1A22

            lda L0065    ; Print key in use
            jsr L339C

            ldx #<L33B5  ; Print 'HOLD + ABORT'
            ldy #>L33B5
            jsr L1A22

            rts

L339C:      sta L0088    ; Save key
            jmp L31CF    ; Print code

L33A4:      .byte yellow+14,6,'KEYS',0,$ff

L33B5:      .byte blue+6,18,'Hold .. ',$27,'H',$27,0
            .byte blue+5,20,'Abort .. Escape +',$27,'H',$27,0,$ff

;------------------------------------------------
; Play sound with movements
;------------------------------------------------

L33E4:      lda L008F              ; Move man sound
            beq L33EB              ; F0 03
            dec L008F              ; C6 8F
            rts                    ; 60

L33EB:      lda L0046              ; Branch if man is moving
            ora L0047
            bne L33F2
            rts

L33F2:      lda L0038              ; Branch every other timer frame
            and #$01
            beq L33F9
            rts

L33F9:      lda L0049              ; Branch if already moving
            bne L3402
	jmp L343C

L3402:      cmp #$01               ; Climbing?
            bne L340B
	ldx #9
            jmp L343E

L340B:
            cmp #$02               ; Jumping?
            bne L3429
            lda L004A
            cmp #$0B
            bcc L341F              ; Branch if still rising in air
	ldx L004A
            jmp L343E              ; Play sound with pitch $BE-2*4A

L341F:
	ldx L004A
             jmp L343E              ; Play sound with pitch $96+2*4A

L3429:      cmp #$03               ; Falling?
            bne L3437
	ldx L004A
            jmp L343E              ; Play sound with pitch $6E-2*4A

L3437:      lda L0046              ; Horizontal movement?
            bne L343C              ; Play sound with pitch $64
            rts

L343C:
	lda $b002
	eor #4
	sta $b002
	rts
L343E:
	ldy #1
	lda #1
	jsr sound

            rts

L344B:      .byte $31,$32,$33,$34,$35,$36,$37,$38
            .byte $39,$30,$31,$32,$33,$34,$35,$36
            .byte $37,$38,$39,$30,$31,$32,$33,$34
            .byte $35,$36,$37,$38,$39,$30,$31,$32
            .byte $33,$34,$35,$36,$37,$38,$39,$30
            .byte $31,$32,$33,$34,$35,$36,$37,$38
            .byte $39,$30,$31,$32,$33,$34,$35,$36
            .byte $37,$38,$39,$30,$31,$32,$33,$34
            .byte $35,$36,$37,$38,$39,$30,$31,$32
            .byte $33,$34,$35,$36,$37

L3498:      .byte $13,$00,$01,$00,$00,$00,$01,$00 ; Sound

            .byte $03,$00,$02,$00
L34A4:      .byte $78,$00
L34A6:      .byte $1E,$00

L34A8:      .byte $10,$00,$03,$00  ; Movement/erase seed sound
L34AC:      .byte $00,$00,$04,$00

L34B0:      .byte $10,$00,$01,$00,$04,$00,$01,$00 ; Update score/bonus

            .byte $00,$00,$00,$00,$00,$00,$00,$00

;------------------------------------------------
; Level datapointers
;------------------------------------------------

L34C0:      .byte <L34D0,>L34D0,<L353E,>L353E
            .byte <L35B2,>L35B2,<L364B,>L364B
            .byte <L36DC,>L36DC,<L376C,>L376C
            .byte <L37E8,>L37E8,<L3872,>L3872

;------------------------------------------------
; Data level 1
;------------------------------------------------

;             +-----------------> walls
;             |   +-------------> ladders
;             |   |   +---------> elevator flag
;             |   |   |   +-----> seed
;             |   |   |   |   +-> birds
L34D0: .byte $0d,$04,$00,$0a,$02

;             Y   X-  X+
       .byte $01,$00,$0F ; Walls
       .byte $05,$01,$0e
       .byte $09,$02,$06
       .byte $09,$0c,$0e
       .byte $0a,$07,$08
       .byte $0b,$09,$0a
       .byte $0c,$0b,$0c
       .byte $0d,$0d,$0d
       .byte $0d,$03,$05
       .byte $0e,$07,$08
       .byte $11,$04,$07
       .byte $11,$09,$0d
       .byte $11,$0f,$0f

       .byte $03,$06,$0b ; Ladders
       .byte $05,$02,$13
       .byte $09,$02,$07
       .byte $0d,$02,$07

       .byte $03,$02,$01,$06,$0b,$06 ; Eggs
       .byte $0e,$06,$02,$0a,$0e,$0a
       .byte $08,$0b,$03,$0e,$07,$0f
       .byte $04,$12,$0a,$12,$0f,$12

       .byte $02,$02,$0b,$02,$04,$06 ; Seed
       .byte $0c,$06,$04,$0a,$0c,$0a
       .byte $08,$0f,$0d,$0e,$07,$12
       .byte $0b,$12

       .byte $04,$0d,$06,$11 ; Birds
       .byte $03,$09,$05,$05,$0a,$01

;------------------------------------------------
; Data level 2
;------------------------------------------------

L353E: .byte $0d,$08,$00,$07,$03

       .byte $01,$00,$02 ; Walls
       .byte $01,$04,$0f
       .byte $05,$00,$05
       .byte $05,$07,$08
       .byte $05,$0a,$0b
       .byte $05,$0d,$0f
       .byte $09,$00,$02
       .byte $09,$04,$0b
       .byte $09,$0d,$0f
       .byte $0d,$00,$08
       .byte $0d,$0a,$0f
       .byte $11,$03,$08
       .byte $11,$0a,$0f

       .byte $01,$02,$0f ; Ladders
       .byte $03,$0e,$13
       .byte $05,$06,$0f
       .byte $07,$02,$07
       .byte $07,$0a,$13
       .byte $0b,$0a,$0f
       .byte $0e,$02,$0b
       .byte $0e,$0e,$13

       .byte $00,$06,$00,$0a,$04,$02 ; Eggs
       .byte $03,$06,$06,$0a,$06,$0e
       .byte $06,$12,$0a,$02,$0b,$06
       .byte $0c,$12,$0f,$0a,$0f,$12

       .byte $00,$02,$00,$0e ; Seed
       .byte $08,$0e,$0a,$12
       .byte $0c,$02,$02,$02
       .byte $0d,$06

       .byte $01,$01,$05,$11,$0e,$09 ; Birds
       .byte $0b,$11,$09,$09

;------------------------------------------------
; Data level 3
;------------------------------------------------

L35B2: .byte $14,$07,$01,$0a,$03

       .byte $01,$00,$01 ; Walls
       .byte $01,$06,$08
       .byte $01,$0a,$0f
       .byte $02,$02,$03
       .byte $05,$0c,$0e
       .byte $06,$06,$09
       .byte $07,$0b,$0b
       .byte $08,$00,$03
       .byte $08,$0c,$0c
       .byte $09,$0e,$0f
       .byte $0b,$0a,$0b
       .byte $0c,$00,$02
       .byte $0c,$0e,$0f
       .byte $0d,$02,$03
       .byte $0d,$0d,$0d
       .byte $0e,$08,$0b
       .byte $0f,$06,$08
       .byte $11,$0c,$0c
       .byte $11,$0e,$0f
       .byte $12,$0a,$0b

       .byte $00,$02,$0a ; Ladders
       .byte $02,$09,$0f
       .byte $06,$07,$11
       .byte $08,$07,$11
       .byte $0a,$0f,$14
       .byte $0e,$02,$07
       .byte $0f,$0a,$0e
     
       .byte $04 ; Elevator

       .byte $03,$09,$01,$0d,$03,$03 ; Eggs
       .byte $03,$0e,$07,$07,$0b,$0c
       .byte $0c,$09,$0c,$02,$0d,$0e
       .byte $0d,$06,$0f,$0f,$0f,$12

       .byte $00,$0d,$01,$02,$01,$09 ; Seed
       .byte $07,$10,$09,$0f,$09,$07
       .byte $0a,$02,$0a,$0c,$0b,$0f
       .byte $0e,$12

       .byte $0e,$05,$02,$0c,$08,$0f ; Birds
       .byte $00,$01,$06,$06

;------------------------------------------------
; Data level 4
;------------------------------------------------

L364B: .byte $18,$05,$01,$06,$04

       .byte $01,$00,$03 ; Walls
       .byte $01,$05,$08
       .byte $01,$0b,$0f
       .byte $04,$0f,$0f
       .byte $05,$00,$03
       .byte $05,$06,$08
       .byte $05,$0b,$0d
       .byte $08,$0e,$0f ; SAMWISE
       .byte $09,$00,$01
       .byte $09,$06,$07
       .byte $0a,$03,$03
       .byte $0a,$0b,$0d
       .byte $0b,$04,$04
       .byte $0c,$06,$07
       .byte $0d,$00,$00 ; SAMWISE
       .byte $0d,$07,$08
       .byte $0e,$02,$02
       .byte $0e,$0b,$0c ; SAMWISE
       .byte $0e,$0f,$0f ; SAMWISE
       .byte $0f,$03,$03
       .byte $10,$04,$04
       .byte $11,$06,$08
       .byte $11,$0b,$0c
       .byte $11,$0e,$0f ; SAMWISE

       .byte $02,$02,$07 ; Ladders
       .byte $07,$02,$13
       .byte $0c,$02,$07
       .byte $0c,$0b,$13
       .byte $0f,$0d,$13

       .byte $09 ; Elevator

       .byte $00,$02,$00,$0a,$00,$0e ; Eggs
       .byte $06,$06,$08,$0e,$0b,$02
       .byte $0d,$06,$0d,$11,$0e,$0e
       .byte $0b,$0b,$0f,$09,$0d,$14

       .byte $00,$06,$05,$02,$0e,$02 ; Seed
       .byte $04,$0c,$08,$12,$0b,$12

       .byte $03,$01,$07,$11,$0d,$01 Birds
       .byte $0e,$11,$08,$05

;------------------------------------------------
; Data level 5
;------------------------------------------------

L36DC: .byte $10,$09,$01,$0d,$04

       .byte $01,$00,$00 ; Walls
       .byte $01,$02,$08
       .byte $01,$0a,$0b
       .byte $01,$0e,$0f
       .byte $05,$00,$04
       .byte $05,$08,$09
       .byte $05,$0b,$0b 
       .byte $09,$00,$04
       .byte $09,$08,$0b
       .byte $09,$0f,$0f
       .byte $0d,$00,$04
       .byte $0f,$09,$0a
       .byte $10,$07,$07
       .byte $11,$03,$05
       .byte $11,$0e,$0f
       .byte $12,$09,$0b

       .byte $02,$02,$07 ; Ladders
       .byte $02,$0a,$0f
       .byte $04,$0a,$13
       .byte $06,$02,$07
       .byte $06,$09,$0e
       .byte $08,$02,$07
       .byte $09,$06,$0b
       .byte $0b,$02,$07
       .byte $09,$10,$14

       .byte $0c ; Elevator

       .byte $00,$02,$00,$06,$00,$0a ; Eggs
       .byte $00,$0e,$04,$06,$07,$11
       .byte $07,$09,$0a,$05,$0a,$13
       .byte $0f,$12,$05,$12,$0f,$0a

       .byte $03,$02,$04,$02,$05,$02 ; Seeds
       .byte $0a,$02,$0e,$02,$0f,$02
       .byte $08,$0a,$0b,$0a,$03,$0e
       .byte $03,$12,$0b,$13,$0e,$12
       .byte $01,$0a

       .byte $01,$05,$01,$0d,$03,$09 ; Birds
       .byte $0a,$09,$0b,$05

;------------------------------------------------
; Data level 6
;------------------------------------------------

L376C: .byte $0f,$06,$01,$07,$04

       .byte $01,$00,$02 ; Walls
       .byte $01,$05,$07
       .byte $01,$0a,$0b
       .byte $05,$00,$01
       .byte $05,$03,$04
       .byte $05,$0b,$0c
       .byte $08,$0e,$0f
       .byte $09,$02,$06
       .byte $09,$0b,$0e
       .byte $0d,$00,$04
       .byte $0d,$0d,$0f
       .byte $11,$05,$05
       .byte $11,$07,$07
       .byte $10,$0b,$0e
       .byte $12,$0e,$0f

       .byte $00,$02,$07 ; Ladders
       .byte $03,$04,$0f
       .byte $0c,$06,$0b
       .byte $0c,$0f,$12
       .byte $0e,$02,$0b
       .byte $0e,$0d,$14

       .byte $08 ; Elevator

       .byte $02,$02,$0d,$02,$04,$06 ; Eggs
       .byte $0b,$06,$0b,$0a,$0d,$0a
       .byte $06,$0e,$0f,$13,$03,$13
       .byte $05,$12,$0b,$11,$0f,$0e

       .byte $00,$0e,$01,$0e,$02,$0e ; Seed
       .byte $06,$0a,$0a,$02
       .byte $0b,$02,$0f,$09

       .byte $01,$01,$03,$0d,$0c,$05 ; Birds
       .byte $0e,$0d,$0e,$08

;------------------------------------------------
; Data level 7
;------------------------------------------------

L37E8: .byte $17,$07,$01,$04,$03

       .byte $01,$03,$04 ; Walls
       .byte $01,$06,$08
       .byte $02,$05,$05
       .byte $02,$09,$09
       .byte $02,$0d,$0d
       .byte $03,$00,$01
       .byte $03,$09,$09
       .byte $03,$0b,$0b
       .byte $05,$01,$03
       .byte $06,$05,$08
       .byte $07,$05,$05
       .byte $07,$0c,$0d
       .byte $08,$05,$05
       .byte $09,$05,$05
       .byte $09,$08,$08
       .byte $09,$00,$02
       .byte $0a,$05,$05
       .byte $0a,$08,$08
       .byte $09,$0a,$0a
       .byte $0c,$0b,$0c
       .byte $0d,$00,$03
       .byte $0d,$05,$06
       .byte $10,$0a,$0d

       .byte $01,$02,$0f ; Ladders
       .byte $03,$02,$07
       .byte $04,$10,$13
       .byte $06,$10,$13
       .byte $08,$10,$13
       .byte $0b,$0d,$12
       .byte $0c,$08,$0e

       .byte $0e ; Elevator

       .byte $02,$03,$05,$12,$07,$12 ; Eggs
       .byte $09,$12,$06,$0e,$07,$07
       .byte $0a,$0a,$0b,$04,$0c,$02
       .byte $0d,$08,$0c,$11,$0d,$0c

       .byte $02,$06,$02,$0e,$08,$07 ; Seed
       .byte $0a,$11

       .byte $01,$0d,$0c,$07,$0b,$10 ; Birds
       .byte $00,$03,$02,$09

;------------------------------------------------
; Data level 8
;------------------------------------------------

L3872: .byte $0f,$06,$00,$0c,$03

       .byte $01,$00,$0f ; Walls
       .byte $05,$02,$03
       .byte $05,$06,$0a
       .byte $05,$0d,$0e
       .byte $09,$02,$04
       .byte $09,$07,$09
       .byte $09,$0c,$0e
       .byte $0d,$03,$05
       .byte $0d,$08,$08
       .byte $0d,$0b,$0d
       .byte $11,$03,$03
       .byte $11,$05,$05
       .byte $11,$07,$09
       .byte $11,$0b,$0b
       .byte $11,$0d,$0d

       .byte $02,$02,$07 ; Ladders
       .byte $03,$0a,$0f
       .byte $08,$06,$0b
       .byte $08,$0e,$13
       .byte $0d,$0a,$0f
       .byte $0e,$02,$07

       .byte $04,$05,$0c,$05,$05,$09 ; Eggs
       .byte $0b,$09,$07,$0d,$09,$0d
       .byte $04,$11,$06,$11,$0a,$11
       .byte $0c,$11,$03,$14,$0d,$14

       .byte $01,$02,$03,$02 ; Seeds
       .byte $04,$02,$05,$02,$07,$02
       .byte $08,$02,$09,$02,$0a,$02
       .byte $0b,$02,$0c,$02,$0d,$02
       .byte $0f,$02

       .byte $08,$11,$08,$09,$0e,$01 ; Birds
       .byte $03,$0d,$0d,$0d


       .byte $55,$42,$28,$34,$29,$3a,$20,$45

;------------------------------------------------
; Clear screen from $8000-$97ff
;------------------------------------------------

clear4:
	lda #$80    ; Clear screen
clearscr:
	sta $91
	lda #0
	sta $90
clear:
	ldy #0
cls:
	sta ($90),y
	iny
	bne cls
	inc $91
	ldx $91
	cpx #$98
	bne clear
	lda #clearmode
	sta $b000
	rts

;------------------------------------------------
; Scankey A
; - A = scancode same as $FE71
; - Exit -> carry set   = key pressed
;           carry clear = key not pressed
;------------------------------------------------

scankey:
	cmp #$80 ; Scan CTRL
	bne sk10
	lda $b001
	and #$40
	bne sk4
	jmp sk13
sk10:
	cmp #$81 ; Scan REPT
	bne sk11
	lda $b002
	and #$40
	bne sk4
	jmp sk13

sk11:
	cmp #$82 ; Scan SHIFT
	bne sk12
	lda $b001
	and #$80
	bne sk4
	jmp sk13

sk12:
	ldx #0
sk1:
	cmp #10
	bcc sk5
	inx
	sec
	sbc #10
	jmp sk1
sk5:
	eor #$ff
	clc
	adc #10
	sta keyrow

	lda #1
	sta keycol

	lda $b000
	and #$f0
	ora keyrow
	sta $b000
sk3:
	cpx #0     ; Set keycol mask
	beq sk2
	dex	
	asl keycol
	jmp sk3
sk2:
	lda $b001  ; Read keycol
	and keycol
	bne sk4
sk13:
	sec
	rts
sk4:
	clc
	rts

keyrow:  .db 0
keycol:  .db 0

