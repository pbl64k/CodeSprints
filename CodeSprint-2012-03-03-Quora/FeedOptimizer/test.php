<?php

	$N = 1000;

	print($N.' 2000 2000'."\n");

	$timestamp = 1;

	for ($i = 0; $i != $N; ++$i)
	{
		$skip = min(rand(1, 20), rand(1, 20));

		$timestamp += $skip;

		if (($i == 0) || rand(0, 1))
		{
			print('S '.$timestamp.' '.rand(10, 10000).' '.rand(20, 100)."\n");
		}
		else
		{
			print('R '.$timestamp."\n");
		}
	}

?>
