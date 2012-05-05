<?php

	$T = intval(readline(''));

	for (; $T; --$T)
	{
		$N = intval(readline(''));

		$adj = array();

		for ($i = 0; $i != $N; ++$i)
		{
			$adj[$i] = array_map('intval', str_split(readline(''), 1));
		}
	}

	$wins = array_map('array_sum', $adj);

	if (count(array_filter($wins, function ($x) { return $x === 0; })) > 1)
	{
		print('No'."\n");
	}
	else
	{
		asort($wins);

		$res = array();

		foreach ($wins as $team => $v)
		{
			$loser = $team;
			$res[] = $team;

			unset($wins[$team]);

			break;
		}

		while (count($wins))
		{
			$winner = NULL;

			foreach ($wins as $team => $v)
			{
				if ($adj[$team][$loser])
				{
					$winner = $team;

					break;
				}
			}

			if (is_null($winner))
			{
				print('No'."\n");

				die();
			}

			$loser = $winner;
			$res[] = $winner;

			unset($wins[$winner]);
		}

		print('Yes '.implode(' ', array_reverse($res))."\n");
	}

?>
