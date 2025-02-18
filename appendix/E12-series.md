
layout: page
title: "The E12 Series"
parent: Appendix
nav_order: 2
---

The E12 series is a standard series of preferred numbers. It is used throughout electronics to provide preferred values for resistors and capacitors.

Specifically, the E12 series provides 12 values for each decade of variation in component values. For resistors, this means that the values are:

{: .note }
10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82

Practically speaking, this means that the resistor values are spaced such that each value is separated by a tolerance of 10%. For example, a resistor value of 100 $\Omega$ with tolerance of 10% could have an actual value of up to 110 $\Omega$. The next value is then chosen such that its minimum value according to the tolerance is 110 $\Omega$, creating a distinct gap between the resister values whilst considering the tolerance. So, the next value is the maximum value of the lower specified value in the series added to value of the tolerance this upper band. This is then rounded to 2 significant figures.

For example, the next value after 100 $\Omega$ is calculated as follows:

10% of 100 $\Omega$ is 10 $\Omega$, therefore the upper band is 100 $\Omega$ + 10 $\Omega$ = 110 $\Omega$.

Then, 10% of 110 $\Omega$ is 11 $\Omega$, therefore the next value in the series is 110 $\Omega$ + 11 $\Omega$ = 121 $\Omega$, rounded to 2 significant figures = 120 $\Omega$.

The next value is then calculated in a similar manner:

10% of 120 $\Omega$ is 12 $\Omega$, therefore the upper band is 120 $\Omega$ + 12 $\Omega$ = 132 $\Omega$. Then, 10% of 132 $\Omega$ is 13.2 $\Omega$, therefore the next value in the series is 132 $\Omega$ + 13.2 $\Omega$ = 145.2 $\Omega$, rounded to 2 significant figures = 150 $\Omega$.

This is a very useful property when designing circuits, as it means that the actual values of the components will be very close to the intended values. This is particularly useful when designing circuits with multiple components, as it means that the actual values of the components will be very close to the intended values.

