<?php

	$nl = 2;
	$nw = 200000;

	$frist = TRUE;

	for ($i = 0; $i !== $nw; ++$i)
	{
		if ($frist)
		{
			$frist = FALSE;
		}
		else
		{
			print(' ');
		}

		genw($nl);
	}

	print("\n".(pow(26, $nl))."\n");

	genallw('', $nl);

	function genallw($prefix, $nl)
	{
		for ($i = 0; $i != 26; ++$i)
		{
			$p = $prefix . chr(ord('a') + $i);

			if ($nl === 1)
			{
				print($p."\n");
			}
			else
			{
				genallw($p, $nl - 1);
			}
		}
	}

	function genw($nl)
	{
		print(chr(ord('a') + rand(0, 25)));

		if ($nl > 1)
		{
			genw($nl - 1);
		}
	}

?>
