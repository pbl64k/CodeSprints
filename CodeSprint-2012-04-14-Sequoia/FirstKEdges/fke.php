<?php

	list($N, $M) = array_map('intval', explode(' ', readline(''), 2));

	$cluster = array();
	$node = array();

	for ($i = 0; $i != $N; ++$i)
	{
		$cluster[$i] = array($i);
		$node[$i] = $i;
	}

	$edges = array();

	for ($i = 0; $i != $M; ++$i)
	{
		$edges[] = array_map('intval', explode(' ', readline(''), 2));
	}

	$clusters = $N;
	$answers = array($clusters);

	for ($i = count($edges) - 1; $i != 0; --$i)
	{
		list($from, $to) = $edges[$i];

		if ($node[$from] !== $node[$to])
		{
			--$clusters;

			foreach ($cluster[$node[$to]] as $n)
			{
				$cluster[$node[$from]][] = $n;
				$node[$n] = $node[$from];
			}
		}

		$answers[] = $clusters;
	}

	for ($i = count($answers) - 1; $i >= 0; --$i)
	{
		print($answers[$i]."\n");
	}

?>
