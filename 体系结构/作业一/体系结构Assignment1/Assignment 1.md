# Assignment 1: Quality Attribute Analysis











































# 刘鹏程

# 171250552











## 一、dependability vs. security

### 1、general scenario and concrete scenario

- **dependability** general scenario
  
  - | Portion of Scenario | Possible Values                                              |
    | ------------------- | ------------------------------------------------------------ |
    | Source              | Large scale, complex systems with availability, safety and<br/> security requirements, physical infrastructure |
    | Stimulus            | fault: incorrect operation, crash, hidden bugs<br />failure: hardware failure, components failure |
    | Artifact            | Code, data persistence, components, redundant storage, <br />hardware support, application interfaces |
    | Environment         | Malicious operation, normal operation, startup, shutdown, repair mode, degraded operation, overloaded operation, running time |
    | Response            | prevent the fault from becoming the failure.  <br />i.e. log the fault; <br />disable the events causing the fault; <br />repair and fix the fault; <br />bug detecting and fixing<br /><br />reduce the cost brought by the failure. <br />i.e. use backup power/storage; <br />temporarily stop related service; <br />operate in a degraded mode while repairing |
  | Response Measure    | Time interval it takes to run normally again when facing a fault/failure<br />MTBF: Mean Time Between Failures<br />MTTR: Mean Time to Repair<br />MTTF: Mean Time to Failure<br />overall cost during the period of repairing and fixing |
  
- **dependability** concrete scenario

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\d2.PNG)

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\d1.PNG)

- **security** general scenario

  - | Portion of Scenario | Possible Values                                              |
    | ------------------- | ------------------------------------------------------------ |
    | Source              | End user, system administrator, system requiring data confidentiality |
    | Stimulus            | Malicious code/attack, identity verification, request permission, authentication and authorization |
    | Artifact            | Code, data, security application interfaces, data encryption |
    | Environment         | Runtime, startup, maintenance time, interaction time         |
    | Response            | Detect and defend the malicious code attack<br />Reply to users' or external entities' request for permission<br />Prepare for accidents that may cause damage and loss to data<br />Test for system defect which may cause data leakage |
    | Response Measure    | Time to complete the verification process<br />Cost of data recovery<br />Time and cost to detect and defend the malicious attack<br />Time and cost to make up for the defect of security mechanism |

- **security** concrete scenario

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sec2.PNG)

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sec1.PNG)

### 2、relationships and differences

- definitions
  - **dependability** in software engineering means the ability to provide services that can defensibly be trusted within a time-period. This may also encompass mechanisms designed to increase and maintain the dependability of a system or software. It reflects the extent of the user's confidence that it will operate as users expect.
  - **security** in software engineering means the ability to continue to function correctly under malicious attack or other hacker risks

- relationships
  - **dependability** covers the related systems attributes of reliability, availability and **security**
  - dependability and security both try to make the system run as usual under malicious attack or other hacker risks. e.g. when some malicious code request to access some top secret database, a dependable system or a secure system will act correspondingly to block such requests. Thus both of them share similar features such as privacy protection. On the other hand, if a system is unable to protect its data from being attacked, it is insecure and cannot be depended on in many cases.
- differences
  - some special dependable systems don't have to satisfy the strict security attribute. e.g. some systems that are very simple may be available only within a small group. There is no need to satisfy the strict security rules because no information about this system has to be secure. This system can gain its dependability by satisfying other related factors.
  - a system that only satisfies the security attribute is far from being dependable. e.g. an accidental hardware failure may make a highly secure system become available, which may lead to the system losing its dependability.

### 3、strategies and tactics

- dependability
  - ![](C:\Users\刘鹏程12138\Desktop\dependability.PNG)
- security
  - ![](C:\Users\刘鹏程12138\Desktop\security.PNG)

## 二、sustainability vs. scalability

### 1、general scenario and concrete scenario

- **sustainability** general scenario 
  
  - | Portion of Scenario | Possible Values                                              |
    | ------------------- | ------------------------------------------------------------ |
    | Source              | a system with the ability to be modified based on stakeholders' changing requirements, end users, developer, system administrator, product manager |
    | Stimulus            | Activities related to software evolution, changes of product needs |
    | Artifact            | Code, data, interfaces, components, resources, configurations... |
    | Environment         | runtime, compile time, build time, initiation time, design time |
    | Response            | Extend the system's ability or meet new requirements<br />Locate and fix an error in the system<br />Port the system from one platform to another |
  | Response Measure    | Time and cost to sustain a software system on an average day<br />Number, size, rate, complexity of affected artifacts when sustaining the system<br />Complexity of new changes or requirements introduced<br />Time and money to add new components or making changes to the system |
  
- **sustainability** concrete scenario

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sus2.PNG)

![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sus1.PNG)

- **scalability** general scenario

  - | Portion of Scenario | Possible Values                                              |
    | ------------------- | ------------------------------------------------------------ |
    | Source              | A system with the ability to meet the increase of resource demand or amount of work, end users, developer, system administrator |
    | Stimulus            | Increase in demand on a system resource such as processing ability, I/O, storage |
    | Artifact            | Code, data, interfaces, components, resources, configurations... |
    | Environment         | Increase in load/demand is transient<br />Increase in load/demand is permanent<br />runtime, design time |
    | Response            | Provides new resources to satisfy the increased load or demand<br />Free and reallocate old resources for the new increased load or demand |
    | Response Measure    | Time and cost to provide new resources to the increased load or demand<br />Time and cost to free and reallocate old resources to the increased load or demand |

- **scalability** concrete scenario

  ![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sca2.PNG)

  ![](C:\Users\刘鹏程12138\Desktop\新建文件夹 (2)\sca1.PNG)

### 2、relationships and differences

- definitions
  - **sustainability** in software engineering means the ability to modify a software system based on stakeholders' changing requirements. It is also described as a mode of software development in which resource use aims to meet product software needs while ensuring the sustainability of natural systems and the environment
  - **scalability** in software engineering means the ability to handle a growing amount of work/demand/load by adding resources to the system. in other words, it means the extent to which software can accommodate horizontal or vertical growth.

- relationships
  - the software **sustainability** can be defined as a measure of a systems' extensibility, interoperability, maintainability, portability, reusability, **scalability**, and usability.
  - sustainability and scalability work together to make the system work normally through a long period of time. Sustainability needs some features of scalability to tackle some strict and unnormal conditions. Scalability ensures that the system can sustain longer and stronger.
- differences
  - suppose that we are developing a ticket reservation system called TRS. TRS has to run normally throughout the whole year except for some special conditions such as Spring Festival travel rush in China. Besides, we hope this system will provide more services in the future, like proposing a travel plan for the visitors, which may consume extra computing and storage effort.
  - if TRS system is scalable, it should be designed to meet the most serious situation such as millions of request happening at the same time. However, scalability alone wouldn't help to add new functions to the software system.
  - if TRS system is sustainable, it should be quickly adjusted to new environment and perform normally as usual. In other words, sustainability makes the software system live longer and healthier. Certainly, the system will also be designed to encounter the problems as peak time request so that it will continue to sustain.

### 3、strategies and tactics

- sustainability
  - ![](C:\Users\刘鹏程12138\Desktop\sustainability.PNG)

- scalability

  - ![](C:\Users\刘鹏程12138\Desktop\scalability.PNG)

  


