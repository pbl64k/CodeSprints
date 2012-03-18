<?php

	error_reporting(E_ALL | E_STRICT);

	function readline_fix($a)
	{
		$str = readline($a);
		//readline($a);
		return $str;
	}

	function p($n, &$v)
	{
		$x = $y = 0;
		$w = $v[$x][$y];

		for ($i = 1; $i != $n; ++$i)
		{
			for ($j = 0; $j != $n; ++$j)
			{
				if ($w <= $v[$i][$j])
				{
					$w = $v[$i][$j];
					$x = $i;
					$y = $j;
				}
			}
		}

		return p0($n, $v, $x, $y);
	}

	function p0($n, &$v, $x, $y)
	{
		$result = array($x, $y);

		$left = $x;
		$right = $y;

		$remaining = array_filter(range(0, $n - 1), function ($u) use ($x, $y) { return ($u != $x) && ($u != $y); });

		$ii = $n - 2;

		for ($i = 0; $i != $ii; ++$i)
		{
			$newcoord = NULL;
			$w = NULL;
			$ww = NULL;

			foreach ($remaining as $r)
			{
				if (is_null($newcoord))
				{
					$newcoord = $r;
					$w = FALSE;
					$ww = $v[$r][$left];
				}

				if ($v[$r][$left] >= $ww)
				{
					$newcoord = $r;
					$w = FALSE;
					$ww = $v[$r][$left];
				}

				if ($v[$right][$r] >= $ww)
				{
					$newcoord = $r;
					$w = TRUE;
					$ww = $v[$right][$r];
				}
			}

			if ($w)
			{
				$result[] = $r;
				$right = $r;
			}
			else
			{
				array_unshift($result, $r);
				$left = $r;
			}

			$remaining = array_filter($remaining, function ($u) use ($r) { return $u != $r; });
		}

		return $result;
	}

	$n = intval(readline_fix(''));

	$v = array();

	for ($i = 0; $i != $n; ++$i)
	{
		$v[$i] = explode(' ', readline_fix(''));
	}

	print(implode(' ', p($n, $v))."\n");

?>
