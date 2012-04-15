<?php

	$bags = array_map('intval', str_split(trim(readline('')), 1));

	$punches = 0;

	function bagcost($i)
	{
		global $bags;

		if ($i < 0 || $i >= count($bags) || $bags[$i] === 0)
		{
			return 0;
		}

		return 1;
	}

	function punchcost($i)
	{
		return bagcost($i - 1) + bagcost($i + 1);
	}

	function splash($i)
	{
		global $bags;

		if ($i < 0 || $i >= count($bags) || $bags[$i] === 0)
		{
			return;
		}

		--$bags[$i];
	}

	function punch($i)
	{
		global $bags, $punches;

		$bags[$i] = 0;

		splash($i - 1);
		splash($i + 1);

		++$punches;
	}

	while (TRUE)
	{
		$tgt = NULL;
		$curcost = 3;

		foreach (range(1, 3) as $bagType)
		{
			foreach ($bags as $i => $type)
			{
				if ($type != $bagType)
				{
					continue;
				}

				$cost = punchcost($i);

				if ($cost < $curcost)
				{
					$curcost = $cost;
					$tgt = $i;
				}
			}

			if (! is_null($tgt))
			{
				break;
			}
		}

		if (is_null($tgt))
		{
			break;
		}

		punch($tgt);
	}

	print($punches."\n");

?>
