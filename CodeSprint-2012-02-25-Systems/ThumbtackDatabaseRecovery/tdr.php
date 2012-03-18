<?php

	//error_reporting(E_ALL | E_STRICT);

	$topLevelLocations = array();
	$knownLocations = array();
	$orphans = array();

	$dealersToLocs = array();
	$locsToDealers = array();

	$names = array();

	while ($line = readline(''))
	{
		list($name0, $price, $geo) = explode(' ', $line, 3);
		$price = substr($price, 1);
		$locations = explode(' ', $geo);

		$name = uniqid('dealer', TRUE);
		$names[$name] = $name0;

		$unknownLocations = array();
		$lowestLevel = 0;
		$parent = NULL;

		foreach ($locations as $loc)
		{
			if (array_key_exists($loc, $knownLocations))
			{
				if ($knownLocations[$loc]['level'] > $lowestLevel)
				{
					$lowestLevel = $knownLocations[$loc]['level'];
					$parent = $loc;
				}
			}
			else
			{
				$unknownLocations[] = $loc;
			}
		}

		if (count($unknownLocations) === 1) // We've managed to find this location's place in the hierarchy!
		{
			$knownLocations[$unknownLocations[0]] = array(
					'level' => $lowestLevel + 1,
					'children' => array(),
					'dealers' => array($name => $price),
					);

			if (! $parent)
			{
				$topLevelLocations[] = $unknownLocations[0];
			}
			else
			{
				$knownLocations[$parent]['children'][] = $unknownLocations[0];
			}

			procDealers($unknownLocations[0]);

			// Now let's see if we can place any other locations thanks to the new information.
			thinkHard($unknownLocations[0], $lowestLevel + 1);
		}
		elseif (! count($unknownLocations))
		{
			$knownLocations[$parent]['dealers'][$name] = $price;
		}
		else // It's not entirely clear where to place this one.
		{
			$dealersToLocs[$name] = array('price' => $price, 'locs' => array());

			foreach ($unknownLocations as $loc)
			{
				if (array_key_exists($loc, $orphans))
				{
					$mergedRelated = $orphans[$loc]['related'];

					foreach ($unknownLocations as $unkLoc)
					{
						if (array_key_exists($unkLoc, $mergedRelated))
						{
							++$mergedRelated[$unkLoc];
						}
						else
						{
							$mergedRelated[$unkLoc] = 1;
						}
					}

					$orphans[$loc] = array(
							'lowestLevel' => max($lowestLevel, $orphans[$loc]['lowestLevel']),
							'parent' => (($lowestLevel > $orphans[$loc]['lowestLevel']) ? $parent : $orphans[$loc]['parent']),
							'related' => $mergedRelated,
							);
				}
				else
				{
					$orphans[$loc] = array(
							'lowestLevel' => $lowestLevel,
							'parent' => $parent,
							'related' => array_combine($unknownLocations, array_map(function ($x) { return 1; }, $unknownLocations)),
							);
				}

				$dealersToLocs[$name]['locs'][$loc] = TRUE;

				if (! array_key_exists($loc, $locsToDealers))
				{
					$locsToDealers[$loc] = array();
				}

				$locsToDealers[$loc][] = $name;
			}
		}
	}

	// Okay, this is where the fun begins. We're likely to have some remaining orphans.

	while (count($orphans))
	{
		gronkulate();
	}

	function gronkulate() // er.
	{
		global $orphans, $knownLocations, $topLevelLocations;

		foreach ($orphans as $loc => $data)
		{
			$curMax = -1;
			$theChosenOne = NULL;

			foreach ($data['related'] as $candidate => $ignored)
			{
				$curCnt = -1;

				foreach ($orphans[$candidate]['related'] as $ign2 => $cnt)
				{
					$curCnt = max($curCnt, $cnt);
				}

				if ($curCnt > $curMax)
				{
					$curMax = $curCnt;
					$theChosenOne = $candidate;
				}
				elseif ($curCnt === $curMax)
				{
					$theChosenOne = NULL;
				}
			}

			if ($theChosenOne)
			{
				$knownLocations[$theChosenOne] = array(
						'level' => $orphans[$theChosenOne]['lowestLevel'] + 1,
						'children' => array(),
						'dealers' => array(),
						);
	
				procDealers($theChosenOne);

				if (! $orphans[$theChosenOne]['parent'])
				{
					$topLevelLocations[] = $theChosenOne;
				}
				else
				{
					$knownLocations[$orphans[$theChosenOne]['parent']]['children'][] = $theChosenOne;
				}
	
				// Now let's see if we can place any other locations thanks to the new information.
				thinkHard($theChosenOne, $orphans[$theChosenOne]['lowestLevel'] + 1);

				return;
			}

			// Nope, that's not it, nothing to be had here.
		}

		// Oh wow. We've sifted through all the orphans without finding any placement candidates! That blows.

		print('ambiguous hierarchy'); // is the /n needed?
		die();
	}

	function thinkHard($loc, $lowestLevel)
	{
		global $orphans, $knownLocations;

		if (! array_key_exists($loc, $orphans))
		{
			return;
		}

		$related = $orphans[$loc]['related'];

		unset($orphans[$loc]);

		foreach ($related as $relLoc => $cnt)
		{
			if ($relLoc != $loc)
			{
				if ($lowestLevel > $orphans[$relLoc]['lowestLevel'])
				{
					$orphans[$relLoc]['lowestLevel'] = $lowestLevel;
					$orphans[$relLoc]['parent'] = $loc;
				}

				unset($orphans[$relLoc]['related'][$loc]);

				if (count($orphans[$relLoc]['related']) === 1) // Yay! Another location placed.
				{
					$knownLocations[$relLoc] = array(
							'level' => $knownLocations[$loc]['level'] + 1,
							'children' => array(),
							'dealers' => array(),
							);

					procDealers($relLoc);

					$knownLocations[$loc]['children'][] = $relLoc;
	
					thinkHard($relLoc, $knownLocations[$loc]['level'] + 1);
				}
			}
		}
	}

	function procDealers($loc)
	{
		global $dealersToLocs, $locsToDealers, $knownLocations;

		if (! array_key_exists($loc, $locsToDealers))
		{
			return;
		}

		foreach ($locsToDealers[$loc] as $dealer)
		{
			if (count($dealersToLocs[$dealer]['locs']) === 1)
			{
				$knownLocations[$loc]['dealers'][$dealer] = $dealersToLocs[$dealer]['price'];
			}

			unset($dealersToLocs[$dealer]['locs'][$loc]);
		}
	}

	foreach ($topLevelLocations as $loc)
	{
		collectStats($loc);
	}

	foreach ($topLevelLocations as $loc)
	{
		printOut($loc);
	}

	function collectStats($loc)
	{
		global $knownLocations;

		$dealNum = count($knownLocations[$loc]['dealers']);
		$total = array_sum($knownLocations[$loc]['dealers']);
	
		foreach ($knownLocations[$loc]['children'] as $child)
		{
			list($dealNumC, $totalC) = collectStats($child);

			$dealNum += $dealNumC;
			$total += $totalC;
		}

		$knownLocations[$loc]['dealNum'] = $dealNum;
		$knownLocations[$loc]['total'] = $total;

		return array($dealNum, $total);
	}

	function printOut($loc, $upAvg = NULL)
	{
		global $knownLocations;

		$avg = $knownLocations[$loc]['total'] / $knownLocations[$loc]['dealNum'];

		$indent = str_repeat('  ', $knownLocations[$loc]['level'] - 1);

		if (is_null($upAvg))
		{
			$dev = '';
		}
		else
		{
			$d = $avg - $upAvg;

			if ($d < 0)
			{
				$dd = '-$'.sprintf('%.2f', -$d);
			}
			else
			{
				$dd = '+$'.sprintf('%.2f', $d);
			}

			if (($dd === '+$0.00') || ($dd === '-$0.00'))
			{
				$dd = 'average';
			}

			$dev = ' ('.$dd.')';
		}

		print($indent.$loc.' $'.sprintf('%.2f', $avg).$dev."\n");

		// print dealers

		global $names;

		$dnames = array();

		foreach ($knownLocations[$loc]['dealers'] as $dname => $price)
		{
			$dnames[] = array($names[$dname], $price);
		}

		usort($dnames, function ($a, $b) { return strcmp(strtolower($a[0]), strtolower($b[0])); });

		foreach ($dnames as $y)
		{
			print($indent.'  - '.$y[0].' $'.$y[1]."\n");
		}

		// print sub-location

		usort($knownLocations[$loc]['children'], function ($a, $b) { return strcmp(strtolower($a), strtolower($b)); });

		foreach ($knownLocations[$loc]['children'] as $child)
		{
			printOut($child, $avg);
		}
	}

?>
