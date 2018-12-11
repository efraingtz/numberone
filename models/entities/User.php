<?
require_once __dir__.'/Entity.php';

/**
 * @Entity @Table(name="one_user")
 **/
class User extends Entity
{

    /**
     * @Id @GeneratedValue @Column(type="integer")
     * @var int
     **/
    public $UserId;

    /**
     * @Column(type="string")
     * @var string
     **/
    public $UserName;


    public function setUserId($userId)
    {
        $this->UserId = $userId;
    }

    public function getUserId()
    {
        return $this->UserId;
    }

    public function setUserName($UserName)
    {
        $this->UserName = $UserName;
    }

    public function getUserName()
    {
        return $this->UserName;
    }
}

?>