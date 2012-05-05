<?php

	list($N, $M) = array_map('intval', explode(' ', readline('')));

	$m = array();

	for ($i = 0; $i != $N; ++$i)
	{
		$m[$i] = array_map('intval', explode(' ', readline('')));
	}

	$n = array();

	for ($i = 0; $i != $M; ++$i)
	{
		for ($j = 0; $j != $N; ++$j)
		{
			$n[$i][$j] = $m[$j][$i];
		}
	}

	$ms = array_map('array_sum', $m);
	$ns = array_map('array_sum', $n);

	$x = array();

	for ($i = 0; $i != $N; ++$i)
	{
		for ($j = 0; $j != $M; ++$j)
		{
			if ($m[$i][$j])
			{
				$x[$i.'-'.$j] = $ms[$i] + $ns[$j] - 2;
			}
		}
	}

	$cnt = 0;

	while (count($x))
	{
		asort($x);

		foreach($x as $k => $v)
		{
			list($i, $j) = explode('-', $k);

			unset($x[$k]);

			break;
		}

		$newx = array();
		$iis = array();
		$jjs = array();

		foreach($x as $k => $v)
		{
			list($ii, $jj) = explode('-', $k);

			if ($ii !== $i && $jj !== $j)
			{
				$newx[$k] = $v;
			}
			elseif ($ii === $i)
			{
				$jjs[] = $jj;
			}
			elseif ($jj === $j)
			{
				$iis[] = $ii;
			}
		}

		$x = $newx;

		$newx = array();

		foreach ($x as $k => $v)
		{
			list($ii, $jj) = explode('-', $k);

			if (in_array($ii, $iis))
			{
				if ($v > 1)
				{
					$newx[$k] = $v - 1;
				}
			}
			elseif (in_array($jj, $jjs))
			{
				if ($v > 1)
				{
					$newx[$k] = $v - 1;
				}
			}
			else
			{
				$newx[$k] = $v;
			}
		}

		$x = $newx;

		++$cnt;
	}

	print($cnt."\n");

?>
