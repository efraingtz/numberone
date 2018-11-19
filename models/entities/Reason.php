<?
include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/entities/Entity.php';

/**
 * @Entity @Table(name="one_reason")
 **/
class Reason extends Entity
{

    /**
     * @Id @GeneratedValue @Column(type="integer")
     * @var int
     **/
    public $ReasonId;

    /**
     * @Column(type="string")
     * @var string
     **/
    public $Reason;

    /**
     * @Column(type="integer")
     * @var int
     **/
    public $UserToId;

    /**
     * @Column(type="integer")
     * @var int
     **/
    public $UserFromId;

    /**
     * @Column(type="integer")
     * @var int
     **/
    public $Priority;

    public function setReasonId($reasonId)
    {
        $this->ReasonId = $reasonId;
    }

    public function getReasonId()
    {
        return $this->ReasonId;
    }

    public function setReason($reason)
    {
        $this->Reason = $reason;
    }

    public function getReason()
    {
        return $this->Reason;
    }

    public function setUserToId($userToId)
    {
        $this->UserToId = $userToId;
    }

    public function getUserToId()
    {
        return $this->UserToId;
    }

    public function setUserFromId($userFromId)
    {
        $this->UserFromId = $userFromId;
    }

    public function getUserFromId()
    {
        return $this->UserFromId;
    }

    public function setPriority($Priority)
    {
        $this->Priority = $Priority;
    }

    public function getPriority()
    {
        return $this->Priority;
    }

}

?>