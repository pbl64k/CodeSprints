<?php

	error_reporting(0);

	gc_enable();

	$n = intval(trim(readline('')));

	for (; $n; --$n)
	{
		$d = trim(readline(''));
		$s = trim(readline(''));

		$a = array();

		$lend = strlen($d);
		$lens = strlen($s);

		for ($i = 0; $i != $lend; ++$i)
		{
			$na = array();

			foreach ($a as $len => $aa)
			{
				foreach ($aa as $cont => $chnk)
				{
					if ($d[$i] == $s[$len])
					{
						if (array_key_exists($len + 1, $na) && array_key_exists(1, $na[$len + 1]))
						{
							$na[$len + 1][1] = min($na[$len + 1][1], $chnk + (($cont == 0) ? 1 : 0));
						}
						else
						{
							$na[$len + 1][1] = $chnk + (($cont == 0) ? 1 : 0);
						}
					}

					if (array_key_exists($len, $na) && array_key_exists(0, $na[$len]))
					{
						$na[$len][0] = min($na[$len][0], $chnk);
					}
					else
					{
						$na[$len][0] = $chnk;
					}
				}
			}

			if ($d[$i] == $s[0])
			{
				$na[1][1] = 1;
			}

			$a = $na;
		}

		$maxl = max(array_keys($a));
		
		if (! array_key_exists(0, $a[$maxl]))
		{
			$minc = $a[$maxl][1];
		}
		elseif (! array_key_exists(1, $a[$maxl]))
		{
			$minc = $a[$maxl][0];
		}
		else
		{
			$minc = min($a[$maxl][0], $a[$maxl][1]);
		}

		print($maxl.' '.$minc."\n");
	}

?>
