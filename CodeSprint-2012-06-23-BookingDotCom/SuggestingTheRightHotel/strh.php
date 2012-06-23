<?php

	/*

	REQUIREMENTS:

	Any PHP 5.3.x from your distro's packages should do.

	TO RUN:

	Put Bookers.csv and Hotels.csv into the same directory as strh.php

	Invoke with:

	time php strh.php >recommendations.csv

	Setting $alt_output to TRUE will produce "human-readable" output to
	stdout instead of a CSV with recommendations.

	*/

	$alt_output = FALSE;

	/*

	REMARKS:

	Honestly, this calls for collaborative filtering, but I'm pretty sure two
	hours wouldn't be enough for me to wrangle all the linear algebra involved
	into submission. Not to mention the need for an efficient gradient descent
	replacement. But if you guys aren't using collaborative filtering for
	this in production, you're doing somethin' wrong. :-)

	This is much simpler and dumber than that. It completely ignores the
	hidden features that can be extracted from other users' preferences, and
	does not take variance of user's preferences into account, using just the
	means. Favoured cities are considered especially important.

	*/

	error_reporting(E_ALL | E_STRICT);

	ini_set('memory_limit', '256M');

	$hdat = rcsv('./Hotels.csv');
	$bdat = rcsv('./Bookers.csv');

	$bookers = array();

	foreach ($bdat as $d)
	{
		if (! array_key_exists($d[0], $bookers))
		{
			$bookers[$d[0]] = array();
		}

		$bookers[$d[0]][] = $d[1];
	}
	
	$hotels = array();
	$hot_c = array();

	foreach ($hdat as $d)
	{
		$d0 = array(
				'city' => $d[1],
				'star' => $d[2] / 5,
				'rev' => ($d[3] - 5) / 5,
				'mp' => ($d[4] > 1000) ? 0 : ($d[4] / 100), // "ignoring" outliers
				);

		$hotels[$d[0]] = $d0;
		$hot_c[$d[1]][$d[0]] = $d0;
	}

	if (! $alt_output)
	{
		print('user_id,rec_hotel_1,rec_hotel_2,rec_hotel_3'."\n");
	}

	foreach ($bookers as $id => $dat)
	{
		$feat = f($id);

		$ccnt = array();

		$fcnt = count($feat);

		$mstar = 0;
		$mrev = 0;
		$mmp = 0;

		foreach ($feat as $x)
		{
			if (! array_key_exists($x['city'], $ccnt))
			{
				$ccnt[$x['city']] = 0;
			}

			$mstar += $x['star'];
			$mrev += $x['rev'];
			$mmp += $x['mp'];

			++$ccnt[$x['city']];
		}

		$ccnt0 = array();

		foreach ($ccnt as $cid => $cccnt)
		{
			if (! array_key_exists($cccnt, $ccnt0))
			{
				$ccnt0[$cccnt] = array();
			}

			$ccnt0[$cccnt][] = $cid;
		}

		krsort($ccnt0);

		reset($ccnt0);
		$v = each($ccnt0);
		$cmc = $v[0];
		$cities = $v[1];

		$mstar /= $fcnt;
		$mrev /= $fcnt;
		$mmp /= $fcnt;

		if ($alt_output)
		{
			print('User #'.$id."\n");
			print('Visited: '.implode(', ', array_unique($dat))."\n");
			print('Favoured cities: '.implode(', ', $cities).' ('.$cmc.')'."\n");
			print(($mstar * 5).' / '.(($mrev * 5) + 5).' / '.($mmp * 100)."\n");
		}

		$rec = rec(3, $dat, $ccnt0, $mstar, $mrev, $mmp);

		if ($alt_output)
		{
			print('Recommended: '.implode(', ', $rec)."\n");

			print("\n");
		}
		else
		{
			print($id.','.implode(',', array_map(function ($x) { return substr($x, 1); }, $rec))."\n");
		}
	}

	function rec($num, $exc, $cit, $mstar, $mrev, $mmp)
	{
		$res = array();

		foreach ($cit as $clst)
		{
			$mres = recc($num - count($res), array_merge($exc, $res), $clst, $mstar, $mrev, $mmp);

			$res = array_merge($res, $mres);

			if (count($res) === $num)
			{
				break;
			}
		}

		return $res;
	}

	function recc($num, $exc, $clst, $mstar, $mrev, $mmp)
	{
		$res = rank($exc, $clst, $mstar, $mrev, $mmp);

		if (empty($res))
		{
			return array();
		}

		return array_slice($res, 0, min($num, count($res)));
	}

	function rank($exc, $clst, $mstar, $mrev, $mmp)
	{
		$res = array();

		foreach ($clst as $city)
		{
			$res = array_merge($res, crank($exc, $city, $mstar, $mrev, $mmp));
		}

		asort($res);

		return array_keys($res);
	}

	function crank($exc, $city, $mstar, $mrev, $mmp)
	{
		global $hot_c;

		$res = array();

		foreach ($hot_c[$city] as $id => $f)
		{
			if (in_array($id, $exc))
			{
				continue;
			}

			$dist = pow($mstar - $f['star'], 2) + pow($mrev - $f['rev'], 2) + pow($mmp - $f['mp'], 2);

			$res['#'.$id] = $dist;
		}

		return $res;
	}

	function f($i)
	{
		global $bookers, $hotels;

		$hot_feat = array_map('g', $bookers[$i]);

		return $hot_feat;
	}

	function g($i)
	{
		global $hotels;

		return $hotels[$i];
	}

	function rcsv($fn)
	{
		$h = fopen($fn, 'r');

		$head = fgetcsv($h);

		$res = array();

		while (($row = fgetcsv($h)) !== FALSE)
		{
			$res[] = $row;
		}

		fclose($h);

		return $res;
	}

?>
