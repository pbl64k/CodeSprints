#!/usr/bin/perl

use strict;
use warnings;

my $elts = 10;
my $maxa = 100;
my $maxw = 100;

print('1'."\n");
print($elts."\n");

for (1 .. $elts)
{
	print((int(rand($maxa)) + 1)." ");
}

print("\n");

for (1 .. $elts)
{
	print((int(rand($maxw)) + 1)." ");
}

print("\n");

1;

