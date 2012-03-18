<?php

	error_reporting(E_ALL | E_STRICT);

	ini_set('memory_limit', '256M');

	final class c
	{
		static private $nm = array();

		final static public function get($n, $m)
		{
			if (array_key_exists($n, self::$nm))
			{
				if (array_key_exists($m, self::$nm[$n]))
				{
					return self::$nm[$n][$m];
				}

				return NULL;
			}

			return NULL;
		}

		final static public function set($n, $m, $x)
		{
			self::$nm[$n][$m] = $x;
		}

		final private function __construct()
		{
		}
	}

	function ct($n, $m)
	{
		$ct = c::get($n, $m);

		if (! is_null($ct))
		{
			return $ct;
		}

		if ($n === $m)
		{
			$ct = 0.0;
		}
		elseif (($n === 1) && ($m === 0))
		{
			$ct = 2.0;
		}
		elseif ($m === 0)
		{
			$ct = (1 + ct($n - 1, 0)) * 2;
		}
		else
		{
			for ($i = ($m + 1); $i != $n; ++$i)
			{
				$ct0 = c::get($n, $i);

				if (! is_null($ct0))
				{
					break;
				}
			}

			for ($i -= 1; $i != $m; --$i)
			{
				$ct1 = 1 + ($ct0 / 2) + (ct($n, 0) / 2);

				c::set($n, $i, $ct1);

				$ct0 = $ct1;
			}

			$ct = 1 + (ct($n, $m + 1) / 2) + (ct($n, 0) / 2);
		}

		c::set($n, $m, $ct);

		return $ct;
	}

	for ($i = 0; $i != 1001; ++$i)
	{
		ct($i, 0);
	}

	$t = readline('');

	for (; $t; --$t)
	{
		list($n, $m) = explode(' ', readline(''), 2);

		printf("%.2f\n", ct(intval($n), intval($m)));
	}

?>
