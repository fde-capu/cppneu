# String : first string must be the name
# string string string ... the scale
# b n		Make n new bias
# x n		Make n new axons
# a|m|p|v	a:action|m:measure|p:physical|v:vital
## Expressors:
# c|o|s|t	c:current
#			o:original threshold
#			s:short threshold
#			t:threshold
# min:max:unit
#
## x123456 : format for setting:
# (use d1234 for d = 0.1234,  d1.0 for d = 1.0)
# oxxxx original threshold
# dxxxx damping 
#
# ixxxx id
#
# todo: h scale-name word word

#Heart v s i42 0:260:bpm Frozen Slow Normal Peaced Accelerated Fast Hyper d9
i42 Heart o3555555 d8999999 v s 0:260:bpm Frozen Slow Normal Peaced Accelerated Fast Hyper

#n Nose o01234567 p o Short Medium Long d1.0
#n Breath v t Empty Neutral Full 0.8
#n Eyes s Closed Normal "Wide Open" Popped d0.4
#n Humor Crappy Bad Medium Ok Good Enthusiastic Incredible
n Tired s
n Drop a
#n Clench a Softly Moderated Hard
#n a Sleep

i2 CustomBiasName o1.0 b s Clear Cloudy Rain Storm 0:100:umity
i4 o099113 d5 b c

b 2
x 2
