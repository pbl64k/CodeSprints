<?php

	function &x(&$opts, &$a, &$w)
	{
		$optsnew = array();

		$anew = $a;
		$wnew = $w;

		$cnt = count($opts);

		if (! $cnt)
		{
			$r = array(array($a, $w));

			return $r;
		}

		$written = FALSE;

		for ($i = 0; $i != $cnt; ++$i)
		{
			$a0 = $opts[$i][0];
			$w0 = $opts[$i][1];

			if ($a0 < $anew)
			{
				$wnew = max($wnew, $w0 + $w);

				$optsnew[] =& $opts[$i];
			}
			elseif ($a0 == $anew)
			{
				$optsnew[] = array($a0, max($w0, $wnew));

				$written = TRUE;
			}
			else
			{
				if (! $written)
				{
					$optsnew[] = array($anew, $wnew);

					$written = TRUE;
				}

				for (; $i != $cnt; ++$i)
				{
					$a0 = $opts[$i][0];
					$w0 = $opts[$i][1];

					if ($w0 > $wnew)
					{
						$optsnew[] = $opts[$i];
					}
				}

				break;
			}
		}

		if (! $written)
		{
			$optsnew[] = array($anew, $wnew);
		}

		return $optsnew;
	}

	function readline_fix($a)
	{
		$str = readline($a);
		readline($a);
		return $str;
	}

	/*
	while (($str = readline_fix('')) !== FALSE)
	{
		print('['.$str.']'."\n");
	}
	*/

	$c = intval(readline_fix(''));

	for (; $c; --$c)
	{
		$n = intval(readline_fix(''));

		$astr = readline_fix('');
		$wstr = readline_fix('');
		/*
		print('['.$astr.']'."\n");
		print('['.$wstr.']'."\n");
		*/

		$as = explode(' ', $astr);
		$ws = explode(' ', $wstr);

		$opts = array();

		for ($i = 0; $i != $n; ++$i)
		{
			$a = intval($as[$i]);
			$w = intval($ws[$i]);

			/*
			print($a.' '.$w."\n");
			*/
			$opts =& x($opts, $a, $w);
		}

		/*
		print_r($opts);
		*/
		$max = 0;

		for ($i = 0; $i != count($opts); ++$i)
		{
			$max = max($max, $opts[$i][1]);
		}

		print($max."\n");
	}


?>
