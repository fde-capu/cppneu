# cppneu
Research project on deep neural networks with genetic algorithms.
---

Artificial Intelligence (AI) has two significant contributors: Machine Learning (ML) and Deep Neural Networks (DNNs). ML employs statistical methods, enabling machines to take conclusions from datasets. DNNs, on the other hand, use non-linear computations to process input signals across neurons, creating a network capable of handling intricate tasks. This project is a DNN system with a layer of genetic algorithms (GA) to permit a process of natural selection.

Some design choices for this model are: neurons connect through layerless sparse axonal connections, intended so the brain complexity surge and adapt by experience during the living period through cadences of synapse engrams. Each neuron can be given a distinct name, to simplify the composition, tracking and understanding of the system, and to facilitate the abstraction and identification of which neurons plays which significant role in the decision making behavior. Reproduction is based on crossing-over and genetic mutation; as passing of generations, different species of beings are expected to happen, adapt and improve over time, mimicking life like organisms in nature.

Neurons form entities, beings. They can actively drive the their own evolution by interacting with each other, generating complexity and scenarios, adding to the overall dynamism. As they interplay, they make use of a reward/correction mechanism that alows them to decide to incentivize behaviors that yield certain outcomes, encouraging others to repeat actions. Beings will carry individual traits and characteristics, act different on each input and scenario, and adapt their performance as they live.

The program operates in real-time. A text-based interface is provided to allow for operations, interference and monitoring of the ecosystem status. This way, the user can experience events first-hand. Everything can be configured, generated and manipulated before or during the run: neurons, beings, objects, behaviors, actions, situations and circumstances. The interface also enables users to assume the roles of any being, bringing a somewhat immersive play.

cppneu is an ongoing project, continuously developed and improved. It is about adapting to code understandings of concepts from neuroscience, behaviournal algorithms, and self development. It will continue to evolve and adapt, just like the beings within the cppneu ecosystem.

---

# Syntax notes for individual neuron definition

## String 
The first string must be the name. All rest is optional. Check header.h for defaults.

## Verbal scale
string string string ...

## Custom measurable scale
min:max:unit 

## Id
ixxxx  id (xxxx as integer), same as nxxxx, or bxxxx for bias.

## Types

| | |
|---|---|
| n | neuron |
| v | vital |
| a | action |
| m | measure |
| p | physical |
| b | bias |
| q | quiet |

## Expressors

| | |
|---|---|
| c | current |
| o | original threshold |
| s | short threshold |
| t | threshold |

## uF notation
For cases >= 0.0, < 1.0, "xxxx" represents "0.xxxx". For 1.0, use "1.0".

## Axons
`in:val:out`, where:

| | |
| --- | --- |
| in | UID or Name |
| val | uF notation multiplier |
| out | UID or Name |

## Auto generation

b n - Make n new bias  
x n - Make n new axons
