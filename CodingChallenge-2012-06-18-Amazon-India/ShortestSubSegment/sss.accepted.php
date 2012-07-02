<?php

	$str = trim(fgets(STDIN));

	$sstr = preg_replace('/[^a-zA-Z\s]/', ' ', $str);

	$wlst = preg_split('/(\s+)/', $sstr, -1, PREG_SPLIT_DELIM_CAPTURE);

	$lsstr = strtolower($sstr);

	$lwlst = preg_split('/\s+/', $lsstr);

	$n = intval(trim(fgets(STDIN)));

	$stlst = array();

	for ($i = 0; $i != $n; ++$i)
	{
		$w = trim(fgets(STDIN));

		$w = preg_replace('/[^a-zA-Z]/', '', strtolower($w));

		$stlst[] = $w;
	}

	$stlst = array_values(array_unique($stlst));

	$n = count($stlst);

	$nlst = array();

	foreach ($lwlst as $j => $lw)
	{
		$nlst[$j] = 0;

		foreach ($stlst as $i => $st)
		{
			if ($lw === $st)
			{
				$nlst[$j] = $i + 1;

				break;
			}
		}
	}

	$nnn = count($nlst);

	$cnt = 0;

	$cnts = array();

	$ws = array();

	for ($i = 0; $i != $nnn; ++$i)
	{
		$nw = $nlst[$i];

		if ($nw === 0)
		{
			continue;
		}

		if (! array_key_exists($nw, $cnts))
		{
			++$cnt;

			$cnts[$nw] = 0;
		}

		++$cnts[$nw];

		$ws[] = array($nw, $i);

		if ($cnt === $n)
		{
			++$i;

			break;
		}
	}

	if ($cnt < $n)
	{
		print('NO SUBSEGMENT FOUND'."\n");

		die();
	}

	$k = 0;
	$kk = count($ws) - 1;
	$j = $ws[$k][1];
	$jj = $ws[$kk][1];

	$bestk = $k;
	$bestkk = $kk;
	$curlen = $jj - $j + 1;

	while ($i !== $nnn)
	{
		while ($cnts[$ws[$k][0]] > 1)
		{
			--$cnts[$ws[$k][0]];
			++$k;
			$j = $ws[$k][1];
		}

		if ($jj - $j + 1 < $curlen)
		{
			$bestk = $k;
			$bestkk = $kk;
			$curlen = $jj - $j + 1;
		}

		$nw = $nlst[$i];

		if ($nw === 0)
		{
			++$i;

			continue;
		}

		++$cnts[$nw];

		$ws[] = array($nw, $i);

		++$kk;
		$jj = $ws[$kk][1];

		++$i;
	}

	while ($cnts[$ws[$k][0]] > 1)
	{
		--$cnts[$ws[$k][0]];
		++$k;
		$j = $ws[$k][1];
	}

	if ($jj - $j + 1 < $curlen)
	{
		$bestk = $k;
		$bestkk = $kk;
		$curlen = $jj - $j + 1;
	}

	prn();

	function prn()
	{
		global $ws, $bestk, $bestkk, $wlst;

		$frist = TRUE;
	
		for ($jjj = $ws[$bestk][1]; $jjj <= $ws[$bestkk][1]; ++$jjj)
		{
			if ($frist)
			{
				$frist = FALSE;
			}
			else
			{
				print(' ');
			}
	
			print($wlst[$jjj * 2]);
		}
	
		print("\n");
	}

?>
