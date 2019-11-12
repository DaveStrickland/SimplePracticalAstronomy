# Simple Practical Astronomy {#mainpage}

[TOC]

# Introduction

Simple Practical Astronomy is a C++ implementation of the astronomical 
algorithms presented by Peter Duffet-Smith in Practical Astronomy With
Your Calculator @cite pawyc_1988.

Although those algorithms lack the accuracy of the modern solutions presented in the
Astronomical Almanac @cite ast_almanac_2009, 
or the Explanatory Supplement to the Astronomical Almanac @cite exp_sup_2013,
they have a pedagogical value in being much simpler and easier to understand. 
To quote Richard Hamming, "The purpose of computing is insight, not numbers."

Having used professional-level libraries such as SOFA, NOVAS, ERFA, other 
implementations of unknown provenance, and partial implementations of
 Meeus's Astronomical Algorithms @cite meeus_1998, I was motivated to create an
implementation of PAWYC in order to be able to obtain:
- The difference in accuracy of these other libraries, compared to the simplest possible algorithm
- The lowest possible computational cost implementation for a given algorithm
- A baseline, first-order-accurate, answer for any interesting value in order
  to have a sanity check on whether code using some other library is working correctly

# Implementation Status

The @ref pawyc_sections table contains a list of the sections defined
in Practical Astronomy With Your Calculator and their implementation 
status in Simple Practical Astronomy.

# Dependencies

This library requires the user to have a working C++11 compiler. At present,
and by design, no external dependencies (e.g. boost) are required.

# Build And Test

Refer to the [build instructions](./build/BUILD.md) on how to build the 
library and its tests. Development and testing has only been done on 
Fedora Linux and OSX 10.11 systems, so it whether it works on other *nix 
systems is unknown although there is no reason to expect it to fail.
