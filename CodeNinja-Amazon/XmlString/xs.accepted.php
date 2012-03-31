<?php

	error_reporting(E_ALL | E_STRICT);

	$struct = explode(' ', trim(readline('')));

	$tags = array();

	preg_match_all('/<(\/?)(.*?)>/', readline(''), $tags, PREG_SET_ORDER);

	$expect = array(0, TRUE);

	$result = array();

	while (TRUE)
	{
		if (! count($tags))
		{
			$tags[0] = array('', '/', $struct[0]);
		}

		if ($expect[1])
		{
			if ($tags[0][1] === '' && $tags[0][2] === $struct[$expect[0]])
			{
				$result[] = $tags[0][1].$tags[0][2];
				array_shift($tags);
			}
			else
			{
				$result[] = $struct[$expect[0]];
			}

			if ($expect[0] === count($struct) - 1)
			{
				$expect[1] = FALSE;
			}
			else
			{
				++$expect[0];
			}
		}
		else
		{
			if ($tags[0][1] === '/' && $tags[0][2] === $struct[$expect[0]])
			{
				$result[] = $tags[0][1].$tags[0][2];
				array_shift($tags);

				if ($expect[0] === 0)
				{
					break;
				}
				else
				{
					--$expect[0];
				}
			}
			elseif (array_search($tags[0][2], $struct) > $expect[0])
			{
				++$expect[0];
				$expect[1] = TRUE;
			}
			else
			{
				$result[] = '/'.$struct[$expect[0]];

				if ($expect[0] === 0)
				{
					break;
				}
				else
				{
					--$expect[0];
				}
			}
		}
	}

	print('<'.implode('><', $result).'>'."\n");

?>
