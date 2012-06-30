<?php

	list($n, $m) = array_map('intval', explode(' ', readline('')));

	$enum = array();
	$e = array();
	$ew = array();

	for ($i = 0; $i != $n; ++$i)
	{
		$enum[$i] = 0;
		$e[$i] = array();
	}

	for ($i = 0; $i != $m; ++$i)
	{
		list($a, $b) = array_map('intval', explode(' ', readline('')));

		--$a;
		--$b;

		++$enum[$a];
		++$enum[$b];

		$e[$a][] = $b;
		$e[$b][] = $a;

		$ew[min($a, $b).'_'.max($a, $b)] = 0;
	}

	$ae = 0;

	while($ae < $m)
	{
		arsort($enum);
	
		foreach ($enum as $nume => $v)
		{
			$tw = 1;
			$ne = 0;

			foreach ($e[$v] as $v1)
			{
				$eew = $ew[min($v, $v1).'_'.max($v, $v1)];

				$tw -= $eew;

				if (! $eew)
				{
					++$ne;
				}
			}

			$avg = $tw / $ne;

			foreach ($e[$v] as $v1)
			{
				$eew = $ew[min($v, $v1).'_'.max($v, $v1)];

				if (! $eew)
				{
					$ew[min($v, $v1).'_'.max($v, $v1)] = $avg;

					++$ae;

					--$enum[$v1];
				}
			}

			$enum[$v] = 0;

			break;
		}
	}

	printf('%.5f', array_sum($ew));
	print("\n");

?>
