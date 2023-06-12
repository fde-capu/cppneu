# String : first string must be the name
# string string string ... any other string is part of the scale
# n|b|x		n:neuron|b:bias|x:axon
# a|m|p|v	a:action|m:measure|p:physical|v:vital
## Expressors:
# c|o|s|t	c:current
#					o:original threshold
#					s:short threshold
#					t:threshold
# min:max:unit
#
## x123456 : format for setting:
# (use d1234 for d = 0.1234 and d1.0 for d = 1.0)
# oxxxx original threshold
# dxxxx damping 
#
# todo: h scale-name word word

n Heart v s 0:260:bpm Frozen Slow Normal Peaced Accelerated Fast Hyper d999

n Nose o01234567 p o Short Medium Long d1.0
#n Breath v t Empty Neutral Full 0.8
#n Eyes s Closed Normal "Wide Open" 0.4
#n Humor Crappy Bad Medium Ok Good Enthusiastic Incredible
#n Tired s
#n Drop a
#n Clench a Softly Moderated Hard
#n a Sleep
b 1
x 1
