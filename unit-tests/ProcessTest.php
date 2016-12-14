<?php

/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          ZhuZongXin <dreamsxin@qq.com>                                 |
  +------------------------------------------------------------------------+
*/

class ProcessTest extends PHPUnit_Framework_TestCase
{
	public function testNormal()
	{
		$process = new Phalcon\Process\Proc('ping -c 1 localhost');
		$this->assertTrue($process->start());

		$ret = $process->read(Phalcon\Process\Proc::STDOUT);

		$this->assertTrue(!empty($ret));
    }

	public function testHandle()
	{
		$process = new Phalcon\Process\Proc('ping -c 1 localhost');
		$this->assertTrue($process->start());

		$ret = NULL;
		$process->handle(function($pipe, $data) use (&$ret) {
			// onread
			$ret = $data;
		},function($pipe){
			// onsend
		},function($pipe, $error){
			// onerror
		},function(){
			// ontimeout
		});

		$this->assertTrue(!empty($ret));
	}
}
