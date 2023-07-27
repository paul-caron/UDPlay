<CsoundSynthesizer>

<CsOptions>

; realtime output
-o dac

</CsOptions>


<CsInstruments>

sr = 44100
ksmps = 32
0dbfs = 1
nchnls = 1

instr 1
 iamp = 1
 icps = p4
 iphs = 0
 iatt = 0.07
 idec = 0.2
 islev = 0.5
 irel = 0.3
 kenv madsr iatt, idec, islev, irel
 aOut oscils iamp, icps, iphs, 0
 out aOut*kenv
endin


instr 2
 kamp  = 1
 kcps  = p4
 iwave = 3 
 kpw init 0.5
 ifn = 1
 asig vco kamp, kcps, iwave, kpw, ifn

 iatt = 0.01
 idec = 0.2
 islev = 0.01
 irel = 0.2
 kenv xadsr iatt, idec, islev, irel
 out asig*kenv

endin


</CsInstruments>


<CsScore>

</CsScore>


</CsoundSynthesizer>


