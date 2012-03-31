<?php

	error_reporting(E_ALL | E_STRICT);

	$tags = array();

	preg_match_all('/<(\/?)(.*?)>/', readline(''), $tags, PREG_SET_ORDER);

	$parents = array();
	$children = array();
	$depth = array();
	$rev_par = array();

	$structure = array();

	function recalc($tag)
	{
		global $parents, $children, $depth;

		$depth[$tag] = $depth[$parents[$tag]] + 1;

		foreach ($children[$tag] as $child)
		{
			recalc($child);
		}
	}

	foreach ($tags as $tag)
	{
		if ($tag[1] === '')
		{
			if (! count($structure))
			{
				$parents[$tag[2]] = 0;
				$depth[$tag[2]] = 0;
				$children[$tag[2]] = array();

				$structure[] = $tag[2];

				continue;
			}
			elseif (($ix = array_search($tag[2], $structure)) !== FALSE)
			{
				$structure = array_slice($structure, 0, $ix);
			}

			$par = $structure[count($structure) - 1];

			if (! array_key_exists($tag[2], $parents))
			{
				$parents[$tag[2]] = $par;
				$depth[$tag[2]] = $depth[$par] + 1;
				$children[$tag[2]] = array();
				$children[$par][] = $tag[2];
			}
			else
			{
				if ($depth[$tag[2]] < $depth[$par] + 1)
				{
					$children[$parents[$tag[2]]] = array_filter($children[$parents[$tag[2]]], function ($x) use($tag) { return $x != $tag[2]; });
					$parents[$tag[2]] = $par;
					$depth[$tag[2]] = $depth[$par] + 1;
					$children[$par][] = $tag[2];
					recalc($tag[2]);
				}
			}

			$structure[] = $tag[2];
		}
		else
		{
			$ix = array_search($tag[2], $structure);

			if ($ix !== FALSE)
			{
				$structure = array_slice($structure, 0, $ix);
			}
			else
			{
				$par = $structure[count($structure) - 1];

				if (! array_key_exists($tag[2], $parents))
				{
					$parents[$tag[2]] = $par;
					$depth[$tag[2]] = $depth[$par] + 1;
					$children[$tag[2]] = array();
					$children[$par][] = $tag[2];
				}
				else
				{
					if ($depth[$tag[2]] < $depth[$par] + 1)
					{
						$children[$parents[$tag[2]]] = array_filter($children[$parents[$tag[2]]], function ($x) use($tag) { return $x != $tag[2]; });
						$parents[$tag[2]] = $par;
						$depth[$tag[2]] = $depth[$par] + 1;
						$children[$par][] = $tag[2];
						recalc($tag[2]);
					}
				}
				/*
				$par = $structure[count($structure) - 1];

				if (! array_key_exists($tag[2], $parents))
				{
					$parents[$tag[2]] = array($par, $parents[$par][1] + 1);
				}
				else
				{
					if ($parents[$tag[2]][1] < $parents[$par][1] + 1)
					{
						$parents[$tag[2]] = array($par, $parents[$par][1] + 1);
					}
				}
				*/
			}
		}
	}

	//print_r($parents);
	//print_r($depth);
	foreach ($parents as $k => $n)
	{
		$rev_par[$n] = $k;
	}

	$k = 0;

	while (array_key_exists($k, $rev_par))
	{
		if ($k)
		{
			print(' ');
		}

		print($rev_par[$k]);

		$k = $rev_par[$k];
	}

	print("\n");

?>
