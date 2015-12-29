;Font file for ASCII chars 32-128

font:
;special chars
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

;ascii chars
.db $00,$00,$00,$00,$00,$00,$00,$00 ; space 
.db $0c,$0c,$0c,$0c,$00,$00,$0c,$00 ; !
.db $cC,$cC,$00,$00,$00,$00,$00,$00 ; "
.db $00,$cC,$Fc,$cC,$cc,$fC,$cC,$00 ; #
.db $30,$30,$3c,$c0,$30,$0C,$f0,$30 ; $
.db $cc,$cc,$0c,$30,$30,$c0,$cc,$cc ; %
.db $30,$cc,$cc,$30,$cf,$cc,$33,$00 ; &
.db $30,$c0,$00,$00,$00,$00,$00,$00 ; '
.db $0c,$30,$30,$30,$30,$30,$0c,$00 ; (
.db $30,$0c,$0c,$0c,$0c,$0c,$30,$00 ; )
.db $00,$cc,$30,$fc,$30,$cc,$00,$00 ; *
.db $00,$30,$30,$FC,$30,$30,$00,$00 ; +
.db $00,$00,$00,$00,$00,$30,$30,$c0 ; ,
.db $00,$00,$00,$FC,$00,$00,$00,$00 ; -
.db $00,$00,$00,$00,$00,$00,$30,$00 ; .
.db $0c,$0C,$0c,$30,$30,$C0,$c0,$c0 ; /

livenum:
.db $30,$cc,$cc,$cc,$cc,$cc,$30,$00 ; 0
.db $30,$f0,$30,$30,$30,$30,$30,$00 ; 1
.db $30,$cc,$0c,$0c,$30,$c0,$Fc,$00 ; 2
.db $30,$cc,$0c,$30,$0c,$cc,$30,$00 ; 3
.db $0c,$3c,$cc,$cc,$cc,$Fc,$0c,$00 ; 4
.db $fc,$c0,$c0,$f0,$0c,$cc,$30,$00 ; 5
.db $0c,$30,$c0,$f0,$cc,$cc,$30,$00 ; 6
.db $fc,$0c,$0c,$30,$C0,$c0,$c0,$00 ; 7
.db $30,$cc,$cc,$30,$cc,$cc,$30,$00 ; 8
.db $30,$cc,$cc,$3c,$0c,$30,$c0,$00 ; 9
.db $00,$30,$30,$00,$30,$30,$00,$00 ; :
.db $00,$30,$30,$00,$30,$30,$c0,$00 ; ;
.db $00,$0c,$30,$c0,$30,$0c,$00,$00 ; <
.db $00,$00,$FC,$00,$00,$FC,$00,$00 ; =
.db $00,$c0,$30,$0c,$30,$c0,$00,$00 ; >
.db $30,$CC,$0C,$30,$30,$00,$30,$00 ; ?
.db $00,$00,$3c,$cc,$cc,$C0,$3c,$00 ; @
.db $30,$cc,$cc,$fc,$cc,$cc,$cc,$00 ; A
.db $f0,$cc,$cc,$f0,$cc,$cc,$f0,$00 ; B
.db $30,$cc,$c0,$c0,$c0,$cc,$30,$00 ; C
.db $f0,$cc,$cc,$cc,$cc,$cc,$f0,$00 ; D
.db $fc,$c0,$c0,$fc,$c0,$c0,$Fc,$00 ; E
.db $fc,$c0,$c0,$f0,$c0,$c0,$c0,$00 ; F
.db $30,$cc,$c0,$c0,$cc,$cc,$3c,$00 ; G
.db $cc,$cc,$cc,$fc,$cc,$cc,$cc,$00 ; H
.db $30,$30,$30,$30,$30,$30,$30,$00 ; I
.db $0c,$0C,$0C,$0C,$0C,$cC,$30,$00 ; J
.db $cc,$cc,$cc,$f0,$cc,$cc,$cc,$00 ; K
.db $c0,$c0,$c0,$c0,$c0,$c0,$fc,$00 ; L
.db $cc,$cc,$fc,$cc,$cc,$cc,$cc,$00 ; M
.db $f0,$cc,$cc,$cc,$cc,$cc,$cc,$00 ; N
.db $30,$cc,$cc,$cc,$cc,$cc,$30,$00 ; O
.db $f0,$cc,$cc,$f0,$c0,$c0,$c0,$00 ; P
.db $30,$cc,$cc,$cc,$fc,$cc,$3c,$00 ; Q
.db $f0,$cc,$cc,$f0,$cc,$cc,$cc,$00 ; R
.db $30,$cc,$c0,$30,$0c,$cc,$30,$00 ; S
.db $fc,$30,$30,$30,$30,$30,$30,$00 ; T
.db $cc,$cc,$cc,$cc,$cc,$cc,$3c,$00 ; U
.db $cc,$cc,$cc,$cc,$cc,$cc,$30,$00 ; V
.db $cc,$cc,$cc,$cc,$fc,$cc,$cc,$00 ; W
.db $cc,$cc,$cc,$30,$cc,$cc,$cc,$00 ; X
.db $cc,$cc,$cc,$fc,$30,$30,$30,$00 ; Y
.db $fc,$0c,$0c,$30,$c0,$c0,$fc,$00 ; Z
.db $f0,$c0,$c0,$c0,$c0,$c0,$f0,$00 ; [
.db $C0,$c0,$c0,$30,$30,$0c,$0c,$0c ; \
.db $3c,$0c,$0c,$0c,$0c,$0c,$3c,$00 ; ]
.db $30,$cc,$00,$00,$00,$00,$00,$00 ; ^
.db $00,$00,$00,$00,$00,$00,$00,$fc ; _
.db $30,$c0,$00,$00,$00,$00,$00,$00 ; `

.db $00,$00,$3C,$CC,$CC,$CC,$3C,$00 ; a
.db $C0,$C0,$f0,$cc,$cc,$cc,$f0,$00 ; b
.db $00,$00,$3c,$c0,$c0,$c0,$3c,$00 ; c
.db $0c,$0c,$3c,$cc,$cc,$cc,$3c,$00 ; d
.db $00,$00,$30,$cc,$fc,$c0,$3c,$00 ; e
.db $3C,$30,$fc,$30,$30,$30,$30,$00 ; f
.db $00,$00,$3c,$cc,$cc,$3c,$cc,$30 ; g
.db $c0,$c0,$fc,$cc,$cc,$cc,$cc,$00 ; h
.db $30,$00,$f0,$30,$30,$30,$fC,$00 ; i
.db $30,$00,$f0,$30,$30,$30,$30,$c0 ; j
.db $c0,$c0,$cc,$f0,$f0,$cc,$cc,$00 ; k
.db $f0,$30,$30,$30,$30,$30,$fC,$00 ; l
.db $00,$00,$cc,$fc,$cc,$cc,$cc,$00 ; m
.db $00,$00,$fc,$cc,$cc,$cc,$cc,$00 ; n
.db $00,$00,$30,$cc,$cc,$cc,$30,$00 ; o
.db $00,$00,$f0,$cc,$cc,$cc,$f0,$c0 ; p
.db $00,$00,$3c,$cc,$cc,$cc,$3c,$0c ; q
.db $00,$00,$fc,$cc,$c0,$c0,$c0,$00 ; r
.db $00,$00,$3c,$c0,$30,$0c,$f0,$00 ; s
.db $30,$30,$fc,$30,$30,$30,$3C,$00 ; t
.db $00,$00,$cc,$cc,$cc,$cc,$fc,$00 ; u
.db $00,$00,$cc,$cc,$cc,$cc,$30,$00 ; v
.db $00,$00,$cc,$cc,$cc,$fc,$cc,$00 ; w
.db $00,$00,$cc,$cc,$30,$cc,$cc,$00 ; x
.db $00,$00,$cc,$cc,$fc,$30,$30,$00 ; y
.db $00,$00,$fc,$0c,$30,$c0,$fc,$00 ; z

.db $0C,$30,$30,$c0,$30,$30,$0C,$00 ; {
.db $0c,$0c,$0c,$0c,$0c,$0c,$0c,$0c ; |
.db $c0,$30,$30,$0C,$30,$30,$c0,$00 ; }
.db $00,$f0,$00,$00,$00,$00,$00,$00 ; ~
.db $ff,$ff,$ff,$ff,$ff,$ff,$ff,$00 ; 

;======================================================================
;FONT ROUTINES:
;======================================================================
;PUTSTRING
; - x,y,string,0
; - x,y,string,0
; - $ff
;
;PUTCHAR x,y,a
;======================================================================
XPOS     equ $90
YPOS     equ $91
COLOR    equ $92
COLORTMP equ $98

PUTSTRING:
    stx $e8
    sty $e9


    ldy #0
P_S_0:
    lda ($e8),y    ; Check end of printing
    cmp #$ff
    beq P_S_4

P_S_1:
    sta XPOS       ; Save x,y,attribute
    jsr setcolor
    jsr PTR_INC
    lda ($e8),y
    sta YPOS

P_S_2:
    jsr PTR_INC    ; Print character until 0
    lda ($e8),y
    beq P_S_5
    jsr PRINTCHAR
    inc XPOS
    jmp P_S_2
P_S_5:
    jsr PTR_INC
    jmp P_S_0

P_S_4:
    rts            ; Return to program

PTR_INC:           ; Increment textpointer
    inc $e8
    bne PTR_1
    inc $e9
PTR_1:
    rts

setcolor:
    sta COLORTMP
    lda XPOS
    and #31
    sta XPOS

    ldx #4
nshift:
    lda COLORTMP
    asl a
    rol COLOR
    asl a
    rol COLOR
    dex
    bne nshift
    rts

;----------------------------------------------------------------------
SCR      equ $93
CHR      equ $95
TMP_Y    equ $97
TMP_A    equ $98

PUTCHAR:
    stx XPOS
    sty YPOS

PRINTCHAR:
    sta TMP_A
    sta CHR        ; Calculate characterspritedata address
    lda #0         ; = A * 8 + charsprite data address
    sta CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    lda CHR
    clc
    adc #<font
    sta CHR
    lda CHR+1
    adc #>font
    sta CHR+1
    
    lda XPOS       ; Calculate screenaddress
    sta SCR
    lda YPOS
    clc
    adc #$80
    sta SCR+1
 
    sty TMP_Y
    ldx #0
    ldy #0         ; Put character on screen
P_C_1:
    lda (CHR),y
    and COLOR
    sta (SCR),y
    inc CHR
    bne P_C_2
    inc CHR+1
P_C_2:
    lda SCR
    clc
    adc #$20
    sta SCR
    lda SCR+1
    adc #0
    sta SCR+1
    inx
    cpx #8
    bne P_C_1

    ldy TMP_Y
    lda TMP_A
    rts
 
INV_CURSOR:
    stx SCR
    tya
    clc
    adc #$80
    sta SCR+1
 
    ldy #0         ; Put character on screen
IC1:
    lda (SCR),y
    eor #$ff
    sta (SCR),y
    tya
    clc
    adc #$20
    tay
    bne IC1
    rts    
