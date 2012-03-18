<?php

	error_reporting(E_ALL | E_STRICT);

	final class EvtMgr
	{
		private $curId = 0;

		private $timeWindow;
		private $maxHeight;

		private $m = array();
		private $stId = 1;

		private $evts = array();

		final static public function mk($timeWindow, $maxHeight)
		{
			return new self($timeWindow, $maxHeight);
		}

		final public function addEvt($timestamp, $score, $height)
		{
			++$this->curId;

			$this->evts[$this->curId] = array(
					'id' => $this->curId,
					'timestamp' => intval($timestamp),
					'score' => intval($score),
					'height' => intval($height),
					);
		}

		final public function reload($timestamp)
		{
			$ts = intval($timestamp);

			$curStId = $this->stId;

			for (; $this->evts[$this->stId]['timestamp'] < ($timestamp - $this->timeWindow); ++$this->stId)
			{
			}

			if ($curStId !== $this->stId)
			{
				$this->m = array();
			}

			return $this->m($this->curId, $this->maxHeight);
		}

		final private function __construct($timeWindow, $maxHeight)
		{
			$this->timeWindow = intval($timeWindow);
			$this->maxHeight = intval($maxHeight);
		}

		final private function m($id, $maxHeight)
		{
			if (($id < $this->stId) || ($maxHeight <= 0))
			{
				return array(
						'score' => 0,
						'numEvts' => 0,
						'evts' => array(),
						);
			}

			if ((! array_key_exists($id, $this->m)) || (! array_key_exists($maxHeight, $this->m[$id])))
			{
				if ($this->evts[$id]['height'] > $maxHeight)
				{
					$this->m[$id][$maxHeight] = $this->m($id - 1, $maxHeight);
				}
				else
				{
					$this->m[$id][$maxHeight] = $this->maxV(
							$this->m($id - 1, $maxHeight),
							$this->m($id - 1, $maxHeight - $this->evts[$id]['height']),
							$id);
				}
			}

			return $this->m[$id][$maxHeight];
		}

		final private function maxV($lst1, $lst2, $evtId)
		{
			$lst2['score'] += $this->evts[$evtId]['score'];
			++$lst2['numEvts'];
			$lst2['evts'][] = $evtId;

			sort($lst2['evts']);

			if ($lst1['score'] < $lst2['score'])
			{
				return $lst2;
			}
			elseif ($lst1['score'] > $lst2['score'])
			{
				return $lst1;
			}
			else
			{
				if ($lst1['numEvts'] < $lst2['numEvts'])
				{
					return $lst1;
				}
				elseif ($lst1['numEvts'] > $lst2['numEvts'])
				{
					return $lst2;
				}
				else
				{
					for ($i = 0; $i != count($lst1); ++$i)
					{
						if ($lst1['evts'][$i] < $lst2['evts'][$i])
						{
							return $lst1;
						}
						elseif ($lst1['evts'][$i] > $lst2['evts'][$i])
						{
							return $lst2;
						}
					}

					return $lst1;
				}
			}
		}
	}

	list($numEvents, $timeWindow, $maxHeight) = explode(' ', readline(''), 3);

	$e = EvtMgr::mk($timeWindow, $maxHeight);

	for ($i = 0; $i != $numEvents; ++$i)
	{
		$line = explode(' ', readline(''));

		$evtCode = array_shift($line);

		if ($evtCode === 'S')
		{
			list($timestamp, $score, $height) = $line;

			$e->addEvt($timestamp, $score, $height);
		}
		else
		{
			list($timestamp) = $line;

			$res = $e->reload($timestamp);

			print($res['score'].' '.$res['numEvts'].' '.implode(' ', $res['evts'])."\n");
		}
	}

?>
