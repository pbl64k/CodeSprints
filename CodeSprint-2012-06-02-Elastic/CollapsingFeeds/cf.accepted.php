<?php

	$R = array();
	
	$C = array();

	$assgn = array();
	$slvd = array();

	while ($l = trim(readline('')))
	{
		$m = array();

		if (preg_match('/^(\d+) Called For Task (\d+) Of (\d+)$/', $l, $m))
		{
			list($a, $emp, $t, $pt) = $m;

			if (! array_key_exists($pt, $C))
			{
				$C[$pt] = array();
			}

			$C[$pt][$t] = TRUE;

			if (! array_key_exists($t, $assgn))
			{
				$assgn[$t] = array();
			}

			$assgn[$t][] = $emp;
		}
		elseif (preg_match('/^(\d+) Called For Task (\d+)$/', $l, $m))
		{
			list($a, $emp, $t) = $m;

			$R[$t] = TRUE;

			if (! array_key_exists($t, $assgn))
			{
				$assgn[$t] = array();
			}

			$assgn[$t][] = $emp;
		}
		elseif (preg_match('/^(\d+) Respond To (\d+)$/', $l, $m))
		{
			list($a, $emp, $t) = $m;

			$slvd[$t] = $emp;
		}
	}

	ksort($R);

	foreach ($R as $t => $b)
	{
		ptask($t);
		pchld($t, 1);
	}

	function ptask($t, $ind = 0)
	{
		global $slvd, $assgn;

		sort($assgn[$t]);

		print(str_repeat('  ', $ind).$t.':'.(array_key_exists($t, $slvd) ? ('Completed:'.$slvd[$t]) : ('InComplete')).':'.implode(':', $assgn[$t])."\n");
	}

	function pchld($t, $ind)
	{
		global $C;

		if (! array_key_exists($t, $C))
		{
			return;
		}

		ksort($C[$t]);

		foreach ($C[$t] as $ct => $b)
		{
			ptask($ct, $ind);
			pchld($ct, $ind + 1);
		}
	}

?>
