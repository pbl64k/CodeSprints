<?php

	error_reporting(0);

	define('F_ORDER_ID', 0);
	define('F_DEAL_ID', 1);
	define('F_EMAIL', 2);
	define('F_ADDR_STREET', 3);
	define('F_ADDR_CITY', 4);
	define('F_ADDR_STATE', 5);
	define('F_ADDR_ZIP', 6);
	define('F_CCN', 7);

	$stateMap = array(
			'ca' => 'ca',
			'il' => 'il',
			'ny' => 'ny',
			'california' => 'ca',
			'illionois' => 'il',
			'new york' => 'ny',
			);

	$cmpMap = array(
			'street' => 'st',
			'road' => 'rd',
			);

	function normalize(array &$fields)
	{
		normalizeEmail($fields[F_EMAIL]);
		normalizeAddrStreet($fields[F_ADDR_STREET]);
		normalizeAddrState($fields[F_ADDR_STATE]);
	}

	function normalizeEmail(&$email)
	{
		list($username, $domain) = explode('@', $email, 2);

		$email = preg_replace('/(\.|\+.*$)/', '', $username).'@'.$domain;
	}

	function normalizeAddrStreet(&$street)
	{
		$tokens = implode(' ', array_map('normalizeAddrStreetComponent', explode(' ', normalizeWhitespace($street))));
	}

	function normalizeAddrStreetComponent($cmp)
	{
		global $cmpMap;

		if (array_key_exists($cmp, $cmpMap))
		{
			return $cmpMap[$cmp];
		}

		return $cmp;
	}

	function normalizeAddrState(&$state)
	{
		global $stateMap;

		if (array_key_exists($state, $stateMap))
		{
			$state = $stateMap[normalizeWhitespace($state)];
		}
	}

	function normalizeWhitespace(&$str)
	{
		return preg_replace('/\W+/', ' ', $str);
	}

	function organize(&$fraudulentDeals, &$case, &$fields, $matchLambda, $diffLambda)
	{
		$match = $matchLambda($fields);
		$diff = $diffLambda($fields);

		if (array_key_exists($match, $case))
		{
			if (count($case[$match]) > 1) // definitely fraudulent
			{
				$fraudulentDeals[intval($fields[F_ORDER_ID])] = TRUE;
			}
			else
			{
				if (array_key_exists($diff, $case[$match])) // ok then
				{
					$case[$match][$diff][] = intval($fields[F_ORDER_ID]);
				}
				else // fraudulent
				{
					foreach ($case[$match] as $orders)
					{
						foreach ($orders as $orderId)
						{
							$fraudulentDeals[$orderId] = TRUE;
						}
					}

					$fraudulentDeals[intval($fields[F_ORDER_ID])] = TRUE;

					$case[$match][$diff] = TRUE;
				}
			}
		}
		else
		{
			$case[$match][$diff] = array(intval($fields[F_ORDER_ID]));
		}
	}

	function getDealIdAndEmail(&$fields)
	{
		return md5($fields[F_DEAL_ID].'+'.$fields[F_EMAIL]);
	}

	function getDealIdAndAddress(&$fields)
	{
		return md5($fields[F_DEAL_ID].'+'.$fields[F_ADDR_STREET].'+'.$fields[F_ADDR_CITY].'+'.$fields[F_ADDR_STATE].'+'.$fields[F_ADDR_ZIP]);
	}

	function getCcn(&$fields)
	{
		return $fields[F_CCN];
	}

	$n = readline('');

	$case1 = array();
	$case2 = array();
	$fraudulentDeals = array();

	for (; $n; --$n)
	{
		$fields = array_map('trim', explode(',', strtolower(readline(''))));

		normalize($fields);

		organize($fraudulentDeals, $case1, $fields, 'getDealIdAndEmail', 'getCcn');
		organize($fraudulentDeals, $case2, $fields, 'getDealIdAndAddress', 'getCcn');
	}

	$k = array_keys($fraudulentDeals);

	sort($k);

	print(implode(',', $k)."\n");

?>
