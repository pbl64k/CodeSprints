<?php

	function Pr($n, $i)
	{
		global $pr, $p, $k;

		$key = $n.'-'.$i;

		if (! array_key_exists($key, $pr))
		{
			if ($i > $n)
			{
				$pr[$key] = 0;
			}
			elseif ($n === 1)
			{
				if ($i === 0)
				{
					$pr[$key] = 1 - $p;
				}
				else
				{
					$pr[$key] = $p;
				}
			}
			elseif ($i === 0)
			{
				$pr[$key] = (1 - Pr0($n - 1)) * (1 - $p);
			}
			else
			{
				$pr[$key] = Pr($n - 1, $i - 1) * $p;
			}
		}

		return $pr[$key];
	}

	function Pr0($n)
	{
		global $pr0, $k;

		if (! array_key_exists($n, $pr0))
		{
			if ($n < $k)
			{
				$pr0[$n] = 0;
			}
			else
			{
				$pr0[$n] = Pr0($n - 1) + Pr($n, $k);
			}
		}

		return $pr0[$n];
	}

	$T = intval(readline(''));

	for (; $T; --$T)
	{
		list($p, $k) = explode(' ', readline(''), 2);
		$p = floatval($p);
		$k = intval($k);
	
		$pr = array();
		$pr0 = array();
	
		$prob = 0;
		$po = 0;
		$exp = 0;
		$exppo = 0;
	
		for ($i = 1; ; ++$i)
		{
			$po += (2 * $i) - 1;
	
			$pcur = Pr($i, $k);
	
			if ($i >= $k && ($pcur < 1e-7))
			{
				break;
			}
	
			$prob += $pcur;
			$exp += $i * $pcur;
			$exppo += $po * $pcur;
		}
	
		print(floor($exp).' '.floor($exppo)."\n");
	}

?>
