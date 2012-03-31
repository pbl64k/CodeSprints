<?php

	$T = readline('');

	for (; $T; --$T)
	{
		$l = readline('');

		$matches = array();

		if (! preg_match('/^ab(a*)bab(a*)$/', $l, $matches))
		{
			print('IMPOSSIBLE'."\n");
		}
		else
		{
			print((3 + (2 + (strlen($matches[1]) * 2)) + (4 + (strlen($matches[2]) * 2)))."\n");
		}
	}

?>
