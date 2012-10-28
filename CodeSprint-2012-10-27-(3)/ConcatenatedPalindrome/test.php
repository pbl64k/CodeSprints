<?php

	$n = 90;
	$m = 30000;

	$c = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890';
	$l = strlen($c);

	print($n.' '.$m."\n");

	for ($i = 0; $i != $n; ++$i)
	{
		for ($j = 0; $j != $m; ++$j)
		{
			print($c[rand(0, $l - 1)]);
		}

		print("\n");
	}

?>
