<?php

	error_reporting(0);

	$K = intval(readline(''));

	$W = array_map('intval', explode(' ', trim(readline(''))));

	$adj = array();

	for ($i = 0; $i != $K; ++$i)
	{
		$line = str_split(trim(readline('')), 1);

		$adj[$i] = array_map(function ($x) { return $x === 'Y' ? 1 : 0; }, $line);
	}

	// find all connected components.

	$V = array_fill(0, $K, 0);

	$comps = array();

	$comp = 1;

	function trav($i, $c)
	{
		global $K, $adj, $V, $comps;
		
		$nodes = array($i);

		while (count($nodes) > 0)
		{
			$k = array_shift($nodes);

			if ($V[$k])
			{
				continue;
			}
	
			if (! array_key_exists($c, $comps))
			{
				$comps[$c] = array();
			}
	
			$V[$k] = $c;
			$comps[$c][] = $k;
	
			for ($j = 0; $j != $K; ++$j)
			{
				if ($adj[$k][$j] || $adj[$j][$k])
				{
					$nodes[] = $j;
				}
			}
		}
	}

	for ($i = 0; $i != $K; ++$i)
	{
		trav($i, $comp);
		++$comp;
	}

	$res = array();

	foreach ($comps as $cc)
	{
		$Ws = array();

		foreach ($cc as $vv)
		{
			$Ws[$vv] = $W[$vv];
		}

		$Wss = $Ws;

		ksort($Ws);
		sort($Wss);

		$Ws = array_combine(array_keys($Ws), array_values($Wss));

		foreach ($Ws as $k => $v)
		{
			$res[$k] = $v;
		}
	}

	ksort($res);

	print(implode(' ', $res)."\n");

?>
