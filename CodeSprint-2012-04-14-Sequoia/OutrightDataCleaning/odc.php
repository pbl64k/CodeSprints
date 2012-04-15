<?php

	$nm = array(
			'Agile Web Solutions St Thomas' => 'agilebits.com',
			'Foreign Transaction Fee' => 'Credit Card Foreign Transaction Fee',
			'Sit4less.com' => 'Sit4Less.com',
			'Amazon.com' => 'Amazon',
			'Alfred App' => 'Alfred',
			'Pragprog Bk' => 'The Pragmatic Bookshelf',
			'Click-to-pay' => 'ICICI Bank Credit Card ',
			'Fs Zenaware' => 'Zenware',
			'Pmgworldwid' => 'PGM World Wide',
			'Sofa Bv' => 'Sofa BV',
			'Dreamhost.com' => 'DreamHost',
			);

	$sg = array(
			'agilebits.com',
			'DreamHost',
			'Panic.com',
			'Alfred',
			'PGM World Wide',
			);

	$nc = array(
			'agilebits.com',
			'Freshbooks',
			'O\'Reilly Media',
			'DreamHost',
			'Alfred',
			'Amazon',
			'Incase Designs',
			);

	$sc = array(
			'agilebits.com',
			'Steven Sacks',
			'Panic.com',
			'Adobe',
			'Lynda.com',
			'Sofa BV',
			'Zenware',
			'Cocoatech',
			);

	$tc = array(
			'Steven Sacks',
			'O\'Reilly Media',
			'Sofa BV',
			);

	$dc = array(
			'Steven Sacks',
			'Sofa BV',
			);

	$N = intval(trim(readline('')));

	$lines = array();

	for ($i = 0; $i != $N; ++$i)
	{
		$lines[] = trim(readline(''));
	}

	$name = array();
	$tags = array();
	$cat = array();

	foreach ($lines as $i => $l)
	{
		$n = n($l);
		$t = t($l, $n);
		$c = c($l, $n);

		//print('['.$l.'] ['.$n.'] ['.implode(', ', $t).'] ['.$c.']'."\n");

		$name[$i] = $n;
		$tags[$i] = $t;
		$cat[$i] = $c;
	}

	if ($name[0] === 'ICICI Bank Credit Card ')
	{
		$name[0] = 'Click-to-pay';
		$tags[0] = array('Credit Card', 'Payment');
	}

	function decap($l)
	{
		return ucfirst(strtolower($l));
	}

	function npostproc($l)
	{
		$matches = array();

		if (preg_match('/^(steven|john|johnny|james|jim|tom|richard|dick|ronald|ron|stephen|michael|mike|william|bill)(.*)$/i', $l, $matches))
		{
			return $matches[1].' '.ucfirst($matches[2]);
		}

		return $l;
	}

	function postproc($l)
	{
		global $nm;

		if (array_key_exists($l, $nm))
		{
			return $nm[$l];
		}

		return npostproc($l);
	}

	function n($l)
	{
		$l = preg_replace('/\bpanic\.com\/cc\b/i', ' panic.com ', $l);
		$l = preg_replace('/[\w\-\.]+@([\w\-]+\.)+[a-z]{2,4}/i', '', $l);
		$l = preg_replace('/[\w\-]+.com\/[a-z]+/i', '', $l);
		$l = preg_replace('/payment,\s+thank\s+you$/i', '', $l);
		$l = preg_replace('/\*interest\s+charge$/i', '', $l);
		$l = preg_replace('/-\s+[a-z]+\s+payment\s+past\s+due$/i', '', $l);
		$l = preg_replace('/\b2ndsite\b/i', '', $l);
		$l = preg_replace('/\bsebastopol\b/i', '', $l);
		$l = preg_replace('/\buniversity\b.*$/i', '', $l);
		$l = preg_replace('/\btransmit\s+(4|for)\b/i', '', $l);
		$l = preg_replace('/\bsystems,?\s+inc\.?/i', '', $l);
		$l = preg_replace('/\bdesigns,?\s+corp\.?/i', 'designs', $l);
		$l = preg_replace('/^[a-z]+\s?\*/i', '', $l);
		$l = preg_replace('/\b\d{10,}\b/', '', $l);
		$l = preg_replace('/\b\d{3}-\d{3}-?\d{4}\b/', '', $l);
		$l = preg_replace('/\b[A-Z]{2}$/', '', $l);

		$l = trim($l);

		$l = preg_replace('/\s+/', ' ', $l);

		$l = implode('', array_map('decap', preg_split('/([^a-z0-9\-])/i', $l, -1, PREG_SPLIT_DELIM_CAPTURE)));

		$l = preg_replace('/\.Com/', '.com', $l);

		$l = postproc($l);

		return $l;
	}

	function t($l, $n)
	{
		global $nc, $sc, $tc, $dc;

		$t = array();

		$m = $n.' '.$l;

		if (preg_match('/\bICICI\b/i', $m))
		{
			$t[] = 'ICICI Bank';
		}

		if (preg_match('/\bcredit\s+cards?\b/i', $m))
		{
			$t[] = 'Credit Card';
		}

		/*
		if (preg_match('/\bpayments?\b/i', $m))
		{
			$t[] = 'Payment';
		}
		*/

		if (preg_match('/\blate\s+fee\b/i', $m))
		{
			$t[] = 'Credit Card';
		}

		if (preg_match('/\bfees?\b/i', $m))
		{
			$t[] = 'Fee';
		}

		if (preg_match('/\bapple\b/i', $m))
		{
			$t[] = 'Apple';
		}

		if (preg_match('/\bstore\b/i', $m))
		{
			$t[] = 'Store';
		}

		if (in_array($n, $nc))
		{
			$t[] = $n;
		}

		if ($n === 'agilebits.com')
		{
			$t[] = 'AGILE WEB SOLUTIONS';
		}

		if (in_array($n, $sc) || preg_match('/(\bsoft|soft\b|\btechno|\bsolu|\bsystem)/i', $m))
		{
			$t[] = 'Software';
		}

		if ($n === 'Woot.com')
		{
			$t[] = 'Webstore';
			$t[] = 'Deals';
		}

		if ($n === 'Freshbooks')
		{
			$t[] = 'Software Service';
		}

		if (in_array($n, $tc))
		{
			$t[] = 'Technology';
		}

		if (in_array($n, $dc))
		{
			$t[] = 'Design';
		}

		if ($n === 'Mi Ranchito' || preg_match('/(\branchito\b|\bresta|\bcafe\b)/i', $m))
		{
			$t[] = 'Restaurant';
		}

		if (preg_match('/host/i', $m))
		{
			$t[] = 'Web Hosting';
		}

		if ($n === 'Sit4Less.com')
		{
			$t[] = 'Office';
			$t[] = 'Furniture';
		}

		if ($n === 'Lynda.com')
		{
			$t[] = 'Training';
		}

		if ($n === 'Alfred')
		{
			$t[] = 'App';
		}

		if ($n === 'The Pragmatic Bookshelf')
		{
			$t[] = 'Books';
		}

		if ($n === 'Incase Designs')
		{
			$t[] = 'Accessories';
		}

		if ($n === 'PGM World Wide')
		{
			$t[] = 'Freight Forwarders';
		}

		if (empty($t))
		{
			$t[] = 'Software';
		}

		return $t;
	}

	function c($l, $n)
	{
		global $sg;

		$m = $n.' '.$l;

		if (preg_match('/(\bcredit\s+cards?\b|\bpayments?\b|\bfees?\b)/i', $m))
		{
			return 'Credit Card Payment';
		}
		elseif (preg_match('/(\branchito\b|\bresta|\bcafe\b)/i', $m))
		{
			return 'Meals & entertainment';
		}
		elseif (preg_match('/(\bdesign|\baccesso)/i', $m))
		{
			return 'Supplies';
		}
		elseif (preg_match('/(\bsit|\bfurni|\boffice\b)/i', $m))
		{
			return 'Office Supplies';
		}
		elseif (preg_match('/(\badvert|\bpromo)/i', $m))
		{
			return 'Advertising';
		}
		elseif (preg_match('/(\bcars?\b|\btrucks?\b)/i', $m))
		{
			return 'Car and truck';
		}
		elseif (preg_match('/(\bdup|\bwrong|\bmistak|\berror)/i', $m))
		{
			return 'Duplicate or Wrong Expenses';
		}
		elseif (preg_match('/\btax\b/i', $m))
		{
			if (preg_match('/\bincome\b/i', $m))
			{
				return 'Estimated and Income Tax Payments';
			}
			elseif (preg_match('/\bsales/b/i', $m))
			{
				return 'Sales Tax Submitted';
			}
			else
			{
				return 'Estimated and Income Tax Payments';
			}
		}
		elseif (preg_match('/(\bmileage\b|\bmiles\b)/i', $m))
		{
			return 'Mileage';
		}
		elseif (in_array($n, $sg))
		{
			return 'Cost of Goods Sold';
		}

		return 'Other expenses';
	}

	foreach ($name as $n) { print($n."\n"); }
	foreach ($tags as $t) { print(implode(', ', $t)."\n"); }
	foreach ($cat as $c) { print($c."\n"); }

?>
