<?php
	
	error_reporting(E_ALL | E_STRICT);

	function set($uid, $ts)
	{
		global $sched;

		del($uid);

		$sched[1][$uid] = $ts;

		if (! array_key_exists($ts, $sched[0]))
		{
			$sched[0][$ts] = array();
		}

		$sched[0][$ts][] = $uid;
	}

	function plist($ts)
	{
		global $sched;

		ksort($sched[0]);

		$frist = TRUE;

		foreach ($sched[0] as $timestamp => &$uids)
		{
			if ($timestamp > $ts)
			{
				break;
			}

			if (empty($uids))
			{
				continue;
			}

			sort($uids);

			if ($frist)
			{
				$frist = FALSE;
			}
			else
			{
				print(' ');
			}

			print(implode(' ', $uids));
		}

		print("\n");
	}

	function del($uid)
	{
		global $sched;

		if (array_key_exists($uid, $sched[1]))
		{
			$ts = $sched[1][$uid];

			unset($sched[1][$uid]);

			$sched[0][$ts] = array_filter($sched[0][$ts], function($x) use($uid) { return $x != $uid; });
		}
	}

	function clean()
	{
		global $sched;

		$sched = array(
				0 => array(),
				1 => array(),
				);
	}

	$fn = dirname(__FILE__).'/stored';

	if (file_exists($fn) && is_readable($fn) && is_writeable($fn))
	{
		$sched = unserialize(file_get_contents($fn));
	}
	else
	{
		clean();
	}

	$N = intval(trim(readline('')));

	for (; $N; --$N)
	{
		$cmd = readline('');

		switch($cmd[0])
		{
			case 's':
				list($c, $uid, $ts) = explode(' ', $cmd);
				set($uid, $ts);
				break;
			case 'l':
				list($c, $ts) = explode(' ', $cmd);
				plist($ts);
				break;
			case 'd':
				list($c, $uid) = explode(' ', $cmd);
				del($uid);
				break;
			case 'c':
				clean();
				break;
		}
	}

	file_put_contents($fn, serialize($sched));

?>
