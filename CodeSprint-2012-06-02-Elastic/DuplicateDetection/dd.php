<?php

	$V = array();
	$E = array();

	$N = intval(trim(readline('')));

	for ($i = 0; $i != $N; ++$i)
	{
		$l = trim(readline(''));

		list($city, $state, $zip, $company, $phone, $email) = explode(',', $l);

		addV('phone:'.$phone);
		addV('mailto:'.$email);
		addE('phone:'.$phone, 'mailto:'.$email);
		addE('mailto:'.$email, 'phone:'.$phone);
	}

	$cnt = 0;

	$lst = array();

	foreach (array_keys($V) as $v)
	{
		$lst[] = $v;

		$unseen = FALSE;

		while (! empty($lst))
		{
			$v0 = array_shift($lst);

			if (! $V[$v0])
			{
				$V[$v0] = 1;

				$unseen = TRUE;

				foreach (array_keys($E[$v0]) as $vc)
				{
					$lst[] = $vc;
				}
			}
		}

		if ($unseen)
		{
			++$cnt;
		}
	}

	print($cnt."\n");

	function addV($v)
	{
		global $V;

		$V[$v] = 0;
	}

	function addE($v1, $v2)
	{
		global $E;

		if (! array_key_exists($v1, $E))
		{
			$E[$v1] = array();
		}

		$E[$v1][$v2] = 1;
	}

?>
