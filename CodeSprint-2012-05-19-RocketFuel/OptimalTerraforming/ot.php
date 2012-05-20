<?php

	error_reporting(E_ALL | E_STRICT);

	gc_enable();

	list($n, $m) = array_map('intval', explode(' ', trim(readline(''))));
	list($px, $py) = array_map('intval', explode(' ', trim(readline(''))));
	list($fx, $fy) = array_map('intval', explode(' ', trim(readline(''))));

	--$px; --$py; --$fx; --$fy;

	$el = array();

	for ($i = 0; $i != $n; ++$i)
	{
		$str = array_map('intval', str_split(readline(''), 1));

		$el[$i] = $str;
	}

	$newpaths = array();

	for ($i = 0; $i <= 9; ++$i)
	{
		$e = $i - $el[$px][$py];

		$newpaths[$px][$py][$i] = array(max($e, 0), array(array($px, $py)));
	}

	$chp = array(array($px, $py));

	$newchp = array();

	while (count($chp))
	{
		iter();

		/*
		for ($i = 0; $i != $n; ++$i)
		{
			if (! isset($newpaths[$i]))
			{
				break;
			}
	
			print(implode(' ', array_map(function($x) { return $x[0]; }, $newpaths[$i]))."\n");
		}

		print("\n");
		*/
	}


	$cost = 0;

	/*
	foreach ($newpaths[$fx][$fy][1] as $pt)
	{
		print($pt[0].' '.$pt[1].' '.$el[$pt[0]][$pt[1]].($frist ? '' : (' '.($el[$pt[0]][$pt[1]] - $el[$oldpt[0]][$oldpt[1]])))."\n");

		if (! $frist)
		{
			$c = $el[$pt[0]][$pt[1]] - $el[$oldpt[0]][$oldpt[1]];

			if ($c > 0)
			{
				$cost += $c;
			}
		}

		$oldpt = $pt;

		$frist = FALSE;
	}
	*/

	print(call_user_func_array('min', array_map(function($x) { return $x[0]; }, $newpaths[$fx][$fy]))."\n");

	function iter()
	{
		global $paths, $chp, $newpaths, $newchp;

		$newchp = array();

		foreach ($chp as $pth)
		{
			iter0($pth[0], $pth[1]);
		}

		$chp = $newchp;
	}

	function iter0($x, $y)
	{
		foreach (array(array(-1, 0), array(0, -1), array(1, 0), array(0, 1)) as $d)
		{
			iter1($x, $y, $x + $d[0], $y + $d[1]);
		}
	}

	function iter1($x, $y, $tx, $ty)
	{
		global $n, $m, $el, $paths, $chp, $newpaths, $newchp;

		if (invalid($tx, $ty))
		{
			return;
		}

		$changed = FALSE;

		$oldnewp = 1000000000000;

		for ($i = 9; $i >= 0; --$i)
		{
			$e = abs($i - $el[$tx][$ty]);
	
			$newp = min($newpaths[$x][$y][$i][0] + $e, $oldnewp);
	
			if ((! isset($newpaths[$tx][$ty][$i])) || $newp < $newpaths[$tx][$ty][$i][0])
			{
				$a = $newpaths[$x][$y][$i][1];
	
				$a[] = array($tx, $ty);
	
				$newpaths[$tx][$ty][$i] = array($newp, $a);
	
				$changed = TRUE;
			}

			$oldnewp = $newp;
		}

		if ($changed)
		{
			$newchp[] = array($tx, $ty);
		}
	}

	function invalid($tx, $ty)
	{
		global $n, $m;

		return $tx < 0 || $ty < 0 || $tx >= $n || $ty >= $m;
	}

?>
