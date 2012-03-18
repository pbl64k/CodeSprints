<?php

	error_reporting(E_ALL | E_STRICT);

	$input = json_decode(readline(''));

	$commits = array();
	$orphansOf = array();

	foreach ($input as $commit)
	{
		$id = sha1($commit);
		$parents = array_map(function ($x) { return substr($x, 8); }, explode("\n", $commit));
		array_pop($parents);

		$knownParents = array();

		foreach ($parents as $parent)
		{
			if (! array_key_exists($parent, $commits))
			{
				if (! array_key_exists($parent, $orphansOf))
				{
					$orphansOf[$parent] = array();
				}
	
				$orphansOf[$parent][] = $id;
			}
			else
			{
				$commits[$parent]['children'][] = $id;
				$knownParents[] = $parent;
			}
		}

		$children = array();

		if (array_key_exists($id, $orphansOf))
		{
			$children = $orphansOf[$id];
			unset($orphansOf[$id]);
			foreach ($children as $child)
			{
				$commits[$child]['parents'][] = $id;
			}
		}

		$commits[$id] = array('commit' => $commit, 'parents' => $knownParents, 'children' => $children);
	}

	$ordered = array();

	foreach ($orphansOf as $orphansList)
	{
		foreach ($orphansList as $orphan)
		{
			process($orphan);
		}
	}

	function process($commit)
	{
		global $commits, $ordered;

		if (! count($commits[$commit]['parents']))
		{
			$ordered[] = $commits[$commit]['commit'];

			foreach ($commits[$commit]['children'] as $child)
			{
				$commits[$child]['parents'] = array_filter($commits[$child]['parents'], function ($parent) use($commit) { return $parent !== $commit; });

				process($child);
			}
		}
	}

	print(json_encode(array_reverse($ordered)));

?>
