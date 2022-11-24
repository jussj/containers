## containers

ft_containers is a school project which goal is to reimplement three containers. In short, these are c++ data structures available to us through the [Standard Template Library](https://en.wikipedia.org/wiki/Standard_Template_Library) used to store elements and providing an unified set of tools to operate on them. Since the standard offers strict guarantees regarding complexity, performance and, let's say, handiness, we are required to follow the same norm the STL implementations apply, called [ISO](https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf).

* ```vector``` a sequence container implemented as an array.

* ```stack``` a container adapter so to speak, because it relies on an underlying container and offer a limited set of tools. ```vector``` is its default in this implementation.

* ```map``` an associative container storing sorted key-value pairs where you access the value through the key. It is implemented as a binary tree and can be ordered according to a sorting criterion.

* ```set``` comes as a bonus, in my implementation it relies on the same red black tree I implemented for ```map```. it is also an associative container, but it doesn't store pairs, only keys.

## usage

my implementations come with a set of tests and a script to compare with the standard output and measure performances.

```make``` will generate binaries for each container implementation.

```make <any container>``` will generate a binary for a particular container.

note that map has an ADVANCED debug option displaying various informations, including a visualizer I used to check the balance of my red black tree, use ```make map DEBUG=1```

```./run_test.sh``` will run tests on all containers.
