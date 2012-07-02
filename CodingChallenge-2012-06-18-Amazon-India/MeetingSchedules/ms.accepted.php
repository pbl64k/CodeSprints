<?php

	list($m, $dur) = array_map('intval', explode(' ', trim(fgets(STDIN))));

	$sch = array(
			array(t(0, 0), t(23, 59), TRUE),
			);

	for ($j = 0; $j != $m; ++$j)
	{
		$a = array_map('intval', explode(' ', trim(fgets(STDIN))));

		$st = t($a[0], $a[1]);
		$en = t($a[2], $a[3]);

		$sch0 = array();

		$changed = FALSE;

		for ($i = 0; $i != count($sch); ++$i)
		{
			list($st0, $en0, $t) = $sch[$i];

			if (! $t)
			{
				$sch0[] = $sch[$i];

				continue;
			}

			if ($st >= $en0 || $en <= $st0)
			{
				$sch0[] = $sch[$i];

				continue;
			}
			elseif ($st <= $st0 && $en >= $en0)
			{
				$sch0[] = array($st0, $en0, FALSE);
			}
			elseif ($st > $st0 && $en < $en0)
			{
				$sch0[] = array($st0, $st, TRUE);
				$sch0[] = array($st, $en, FALSE);
				$sch0[] = array($en, $en0, TRUE);
			}
			elseif ($st > $st0)
			{
				$sch0[] = array($st0, $st, TRUE);
				$sch0[] = array($st, $en0, FALSE);
			}
			elseif ($en < $en0)
			{
				$sch0[] = array($st0, $en, FALSE);
				$sch0[] = array($en, $en0, TRUE);
			}
			else
			{
				$sch0[] = $sch[$i];

				continue;
			}

			$changed = TRUE;
		}

		// normalize

		if ($changed)
		{
			$sch1 = array();

			$cur = $sch0[0];

			for ($i = 1; $i != count($sch0); ++$i)
			{
				if ($cur[2] === $sch0[$i][2])
				{
					$cur[1] = $sch0[$i][1];
				}
				else
				{
					$sch1[] = $cur;

					$cur = $sch0[$i];
				}
			}

			$sch1[] = $cur;

			$sch = $sch1;
		}
	}

	foreach ($sch as $k)
	{
		//print(t0($k[0]).' '.t0($k[1]).' '.($k[2] ? ' ' : 'X')."\n");

		if ($k[2] && $k[1] - $k[0] >= $dur)
		{
			print(t0($k[0]).' '.t0($k[1])."\n");
		}
	}

	function t($h, $m)
	{
		return $h * 60 + $m;
	}

	function t0($x)
	{
		if ($x === t(23, 59))
		{
			return '00 00';
		}

		return str_pad(strval(floor($x / 60)), 2, '0', STR_PAD_LEFT).' '.str_pad(strval($x % 60), 2, '0', STR_PAD_LEFT);
	}

?>
