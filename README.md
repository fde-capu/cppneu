# cppneu
Research project focused on deep neural networks. 

## String 
The first string must be the name. All rest is optional. Check header.h for defaults.

## Verbal scale
string string string ...

## Custom measurable scale
min:max:unit 

## Id
ixxxx  id (xxxx as integer), same as nxxxx, or bxxxx for bias.

## Types

| n | neuron |
| v | vital |
| a | action |
| m | measure |
| p | physical |
| b | bias |
| q | quiet |

## Expressors

| c | current |
| o | original threshold |
| s | short threshold |
| t | threshold |

## uF notation
For cases >= 0.0, < 1.0, "xxxx" represents "0.xxxx". For 1.0, use "1.0".

## Axons

| Axons | Description |
| --- | --- |
| in | UID or Name |
| val | uF notation multiplier |
| out | UID or Name |

b n - Make n new bias  
x n - Make n new axons
